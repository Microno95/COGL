//
// Created by ekin4 on 7/2/2018.
//

#ifndef COGL_MESHSKELETON_H
#define COGL_MESHSKELETON_H

#include <utility>
#include "Renderable.h"

namespace cogl {
    class MeshRepresentation {
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        MeshRepresentation(const std::vector<Vertex> &vertices) : vertices(vertices) {
            indices = std::vector<unsigned int>();
            for (unsigned int i = 0; i < vertices.size(); i++) indices.push_back(i);
        }

        MeshRepresentation(std::vector<Vertex> mesh_verts, std::vector<unsigned int> mesh_indices) : vertices(
                std::move(mesh_verts)), indices(std::move(mesh_indices)) {}

		MeshRepresentation& mergeRepresentations(MeshRepresentation other) {
			auto initial_size = vertices.size();
			vertices.insert(std::end(vertices), std::begin(other.vertices), std::end(other.vertices));
			auto other_indices = other.indices;
			for (auto &i : other_indices) i += initial_size;
			indices.insert(std::end(indices), std::begin(other_indices), std::end(other_indices));
			return *this;
		}

		MeshRepresentation& mergeRepresentations(const std::vector<MeshRepresentation> &other_reps) {
            auto initial_size = vertices.size();
            for (auto &other : other_reps) {
                vertices.insert(std::end(vertices), std::begin(other.vertices), std::end(other.vertices));
                auto other_indices = other.indices;
                for (auto &i : other_indices) i += initial_size;
                indices.insert(std::end(indices), std::begin(other_indices), std::end(other_indices));
                initial_size = vertices.size();
            }
            return *this;
        }

        MeshRepresentation& mergeRepresentations(MeshRepresentation other, const glm::mat4 transform) {
            auto initial_size = vertices.size();
            vertices.insert(std::end(vertices), std::begin(other.vertices), std::end(other.vertices));
            auto start_iter = std::begin(vertices);
            std::advance(start_iter, initial_size);
            std::for_each(start_iter, std::end(vertices), [&](Vertex & i)
            {
                glm::vec4 temp{i.x, i.y, i.z, i.w};
                temp = transform * temp;
                i.x = temp.x;
                i.y = temp.y;
                i.z = temp.z;
				i.w = temp.w;
            });
            auto other_indices = other.indices;
            for (auto &i : other_indices) i += initial_size;
            indices.insert(std::end(indices), std::begin(other_indices), std::end(other_indices));
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &outstream, const MeshRepresentation &rhs) {
            for (auto &i : rhs.vertices) {
                outstream << "v " << i.x << " " << i.y << " " << i.z << " " << i.k << std::endl;
            }
            for (auto &i : rhs.vertices) {
                outstream << "vt " << i.u << " " << i.v << " " << i.w << " " << i.p << std::endl;
            }
            for (auto &i : rhs.vertices) {
                outstream << "vn " << i.nx << " " << i.ny << " " << i.nz << " " << i.nw << std::endl;
            }
            for (auto i = 0; i < rhs.indices.size(); i += 3) {
                outstream << "f " << rhs.indices[i] + 1 << "/" << rhs.indices[i] + 1 << "/" << rhs.indices[i] + 1;
                outstream << " " << rhs.indices[i+1] + 1 << "/" << rhs.indices[i+1] + 1 << "/" << rhs.indices[i+1] + 1;
                outstream << " " << rhs.indices[i+2] + 1 << "/" << rhs.indices[i+2] + 1 << "/" << rhs.indices[i+2] + 1;
                outstream << std::endl;
            }
            return outstream;
        }

        static void set_to_split(const std::string &to_split, const std::string &delim, glm::vec4 &output) {
            auto string_tokens = cogl::utilities::split_string(to_split, delim, false);
            if (string_tokens.size() == 1) {
                output.x = std::stof(string_tokens[0]);
            } else if (string_tokens.size() == 2) {
                output.x = std::stof(string_tokens[0]);
                output.y = std::stof(string_tokens[1]);
            } else if (string_tokens.size() == 3) {
                output.x = std::stof(string_tokens[0]);
                output.y = std::stof(string_tokens[1]);
                output.z = std::stof(string_tokens[2]);
            } else if (string_tokens.size() == 4) {
                output.x = std::stof(string_tokens[0]);
                output.y = std::stof(string_tokens[1]);
                output.z = std::stof(string_tokens[2]);
                output.w = std::stof(string_tokens[3]);
            }
        }

        static void set_to_split(const std::string &to_split, const std::string &delim, Vertex &output) {
            auto string_tokens = cogl::utilities::split_string(to_split, delim, false);
            if (string_tokens.size() == 1) {
                output.x = std::stof(string_tokens[0]);
            } else if (string_tokens.size() == 2) {
                output.x = std::stof(string_tokens[0]);
                output.y = std::stof(string_tokens[1]);
            } else if (string_tokens.size() == 3) {
                output.x = std::stof(string_tokens[0]);
                output.y = std::stof(string_tokens[1]);
                output.z = std::stof(string_tokens[2]);
            } else if (string_tokens.size() == 4) {
                output.x = std::stof(string_tokens[0]);
                output.y = std::stof(string_tokens[1]);
                output.z = std::stof(string_tokens[2]);
                output.w = std::stof(string_tokens[3]);
            }
        };

        static std::vector<cogl::MeshRepresentation> parse_obj(const std::vector<std::string> &objectCode) {
            std::vector<cogl::MeshRepresentation> objects_in_obj;

            auto first = std::find_if(objectCode.begin(), objectCode.end(), [&](const std::string& x){return cogl::utilities::begins_with(x, std::string("o "));});
            auto next = std::find_if(std::next(first, 1), objectCode.end(), [&](const std::string& x){return cogl::utilities::begins_with(x, std::string("o "));});
            auto verticesVector = parse_vertices(objectCode);
            auto texCoordsVector = parse_texture_coordinates(objectCode);
            auto normalsVector = parse_normals(objectCode);

            if (first == next) {
                first = objectCode.begin();
                next = objectCode.end();
            }

            while (first != next) {
                objects_in_obj.push_back(create_MeshRepresentation_from_obj(std::vector<std::string>(first, next), verticesVector, texCoordsVector, normalsVector));
                first = std::find_if(std::next(first, 1), objectCode.end(), [&](const std::string& x){return cogl::utilities::begins_with(x, std::string("o "));});
                next = std::find_if(std::next(first, 1), objectCode.end(), [&](const std::string& x){return cogl::utilities::begins_with(x, std::string("o "));});
            }

            return std::move(objects_in_obj);
        };

        static std::vector<cogl::Vertex> parse_vertices(const std::vector<std::string> &objectCode) {
            std::vector<Vertex> verticesVector;
            Vertex temp2{};

            for (auto &i : objectCode) {
                if (cogl::utilities::begins_with<std::string>(i, "v ")) {
                    temp2.k = 1.0;
                    set_to_split(std::string(std::next(i.begin(), 2), i.end()), " ", temp2);
                    temp2.nw = 0;
                    temp2.p = 0;
                    verticesVector.push_back(temp2);
                }
            }

            return std::move(verticesVector);
        };

        static std::vector<glm::vec4> parse_normals(const std::vector<std::string> &objectCode) {
            std::vector<glm::vec4> normalsVector;
            glm::vec4 temp2(0);
            for (auto &i : objectCode) {
                if (cogl::utilities::begins_with<std::string>(i, "vn ")) {
                    temp2 = {0,0,0,0};
                    set_to_split(std::string(std::next(i.begin(), 3), i.end()), " ", temp2);
                    normalsVector.push_back(temp2);
                }
            }

            return std::move(normalsVector);
        }

        static std::vector<glm::vec4> parse_texture_coordinates(const std::vector<std::string> &objectCode) {
            std::vector<glm::vec4> texCoordsVector;
            glm::vec4 temp2(0);
            for (auto &i : objectCode) {
                if (cogl::utilities::begins_with<std::string>(i, "vt ")) {
                    temp2 = {0,0,0,0};
                    set_to_split(std::string(std::next(i.begin(), 3), i.end()), " ", temp2);
                    texCoordsVector.push_back(temp2);
                }
            }

            return std::move(texCoordsVector);
        }

        static MeshRepresentation create_MeshRepresentation_from_obj(const std::vector<std::string> &objectCode, std::vector<Vertex> verticesVector, std::vector<glm::vec4> texCoordsVector, std::vector<glm::vec4> normalsVector) {
            std::vector<Vertex> retVertices;
            std::vector<unsigned int> retIndices;
            unsigned int index_count = 0;

            for (auto &i : objectCode) {
                if (cogl::utilities::begins_with<std::string>(i, "f ")) {
                    std::string temp(i);
                    std::vector<std::string> temp3;
                    unsigned int temp4, temp5, temp6;
                    temp.erase(0, 2);
                    auto temp2 = cogl::utilities::split_string(temp, " ", true);
                    for (auto &subtemp : temp2) {
                        if (temp2.size() == 3) {
                            temp3 = cogl::utilities::split_string(subtemp, "/", true);
                            if (!temp3.empty() && temp3.size() <= 3) {
                                retVertices.push_back(verticesVector[std::stoul(temp3[0]) - 1]);
                                retIndices.push_back(index_count++);
                                if (temp3.size() == 2) {
                                    if (!temp3[1].empty()) temp5 = std::stoul(temp3[1]);
                                    else temp5 = 1;
                                    if (!temp3[1].empty()) {
                                        retVertices[index_count - 1].u = texCoordsVector[temp5 - 1].x;
                                        retVertices[index_count - 1].v = texCoordsVector[temp5 - 1].y;
                                        retVertices[index_count - 1].w = texCoordsVector[temp5 - 1].z;
                                        retVertices[index_count - 1].p = texCoordsVector[temp5 - 1].w;
                                    }
                                } else if (temp3.size() == 3) {
                                    if (!temp3[2].empty()) temp5 = std::stoul(temp3[2]);
                                    else temp5 = 1;
                                    if (!temp3[1].empty()) temp6 = std::stoul(temp3[1]);
                                    else temp6 = 1;

                                    retVertices[index_count - 1].nx = normalsVector[temp5 - 1].x;
                                    retVertices[index_count - 1].ny = normalsVector[temp5 - 1].y;
                                    retVertices[index_count - 1].nz = normalsVector[temp5 - 1].z;
                                    retVertices[index_count - 1].nw = normalsVector[temp5 - 1].w;

                                    if (!temp3[1].empty()) {
                                        retVertices[index_count - 1].u = texCoordsVector[temp6 - 1].x;
                                        retVertices[index_count - 1].v = texCoordsVector[temp6 - 1].y;
                                        retVertices[index_count - 1].w = texCoordsVector[temp6 - 1].z;
                                        retVertices[index_count - 1].p = texCoordsVector[temp6 - 1].w;
                                    }
                                }
                            }

                        }
                    }
                }
            }

            return std::move(MeshRepresentation(retVertices, retIndices));
        }

        static std::vector<MeshRepresentation> load_from_obj(const std::string &obj_filepath) {
            return std::move(parse_obj(cogl::utilities::read_text_to_vector(obj_filepath)));
        }

        static const MeshRepresentation Cube;
        static const MeshRepresentation Icosahedron;

    };
}

#endif //COGL_MESHSKELETON_H

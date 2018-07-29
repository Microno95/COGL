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

        static MeshRepresentation load_from_obj(const std::string &filename) {
            std::vector<Vertex> verticesVector;
            std::vector<unsigned int> indicesVector;
            std::vector<glm::vec4> normalsVector;
            std::vector<glm::vec4> texCoordsVector;

            // Read the Vertex Shader code from the file
            std::vector<std::string> objectCode;
            std::ifstream objectStream(filename, std::ios::in);
            if (objectStream.is_open()) {
                std::string Line;
                while (getline(objectStream, Line))
                    objectCode.emplace_back(Line);
                objectStream.close();
            } else {
                printf("Impossible to open %s. Are you in the right directory?\n", filename.c_str());
                getchar();
            }

            for (auto &i : objectCode) {
                if (cogl::utilities::begins_with<std::string>(i, "v ")) {
                    std::string temp(i);
                    temp.erase(0, 3);
                    std::vector<std::string> temp3 = cogl::utilities::split_string(temp, " ", true);
                    Vertex temp2{};
                    temp2.x = 0;
                    temp2.y = 0;
                    temp2.z = 0;
                    temp2.k = 0;
                    if (temp3.size() == 1) {
                        temp2.x = std::stof(temp3[0]);
                    } else if (temp3.size() == 2) {
                        temp2.x = std::stof(temp3[0]);
                        temp2.y = std::stof(temp3[1]);
                    } else if (temp3.size() == 3) {
                        temp2.x = std::stof(temp3[0]);
                        temp2.y = std::stof(temp3[1]);
                        temp2.z = std::stof(temp3[2]);
                    }
                    temp2.k = 1.0;
                    temp2.nx = 0;
                    temp2.ny = 0;
                    temp2.nz = 0;
                    temp2.nw = -1;
                    temp2.u = 0;
                    temp2.v = 0;
                    temp2.w = 0;
                    temp2.p = -1;
                    verticesVector.push_back(temp2);
                } else if (cogl::utilities::begins_with<std::string>(i, "vt ")) {
                    std::string temp(i);
                    glm::vec4 temp2;
                    temp.erase(0, 3);
                    std::vector<std::string> temp3 = cogl::utilities::split_string(temp, " ", true);
                    temp2.x = 0;
                    temp2.y = 0;
                    temp2.z = 0;
                    temp2.w = 0;
                    if (temp3.size() == 1) {
                        temp2.x = std::stof(temp3[0]);
                    } else if (temp3.size() == 2) {
                        temp2.x = std::stof(temp3[0]);
                        temp2.y = std::stof(temp3[1]);
                    } else if (temp3.size() == 3) {
                        temp2.x = std::stof(temp3[0]);
                        temp2.y = std::stof(temp3[1]);
                        temp2.z = std::stof(temp3[2]);
                    } else if (temp3.size() == 4) {
                        temp2.x = std::stof(temp3[0]);
                        temp2.y = std::stof(temp3[1]);
                        temp2.z = std::stof(temp3[2]);
                        temp2.w = std::stof(temp3[3]);
                    }
                    texCoordsVector.push_back(temp2);
                } else if (cogl::utilities::begins_with<std::string>(i, "vn ")) {
                    std::string temp(i);
                    glm::vec4 temp2;
                    temp.erase(0, 3);
                    std::vector<std::string> temp3 = cogl::utilities::split_string(temp, " ", true);
                    temp2.x = 0;
                    temp2.y = 0;
                    temp2.z = 0;
                    temp2.w = 0;
                    if (temp3.size() == 1) {
                        temp2.x = std::stof(temp3[0]);
                    } else if (temp3.size() == 2) {
                        temp2.x = std::stof(temp3[0]);
                        temp2.y = std::stof(temp3[1]);
                    } else if (temp3.size() == 3) {
                        temp2.x = std::stof(temp3[0]);
                        temp2.y = std::stof(temp3[1]);
                        temp2.z = std::stof(temp3[2]);
                    } else if (temp3.size() == 4) {
                        temp2.x = std::stof(temp3[0]);
                        temp2.y = std::stof(temp3[1]);
                        temp2.z = std::stof(temp3[2]);
                        temp2.w = std::stof(temp3[3]);
                    }
                    normalsVector.push_back(temp2);
                } else if (cogl::utilities::begins_with<std::string>(i, "f ")) {
                    std::string temp(i);
                    std::vector<std::string> temp3;
                    unsigned int temp4, temp5, temp6;
                    temp.erase(0, 2);
                    auto temp2 = cogl::utilities::split_string(temp, " ", true);
                    for (auto &subtemp : temp2) {
                        {
                            temp3 = cogl::utilities::split_string(subtemp, "/", true);
                            if (temp3.size() == 1) {
                                std::stringstream(temp3[0]) >> temp4;
                                indicesVector.push_back(temp4 - 1);
                            } else if (temp3.size() == 2) {
                                std::stringstream(temp3[0]) >> temp4;
                                std::stringstream(temp3[1]) >> temp5;
                                if (std::round(verticesVector[temp4 - 1].nw) != temp5 - 1) {
                                    if (verticesVector[temp4 - 1].nw < 0) {
                                        verticesVector[temp4 - 1].nx = normalsVector[temp5 - 1].x;
                                        verticesVector[temp4 - 1].ny = normalsVector[temp5 - 1].y;
                                        verticesVector[temp4 - 1].nz = normalsVector[temp5 - 1].z;
                                        verticesVector[temp4 - 1].nw = temp5 - 1;
                                        indicesVector.push_back(temp4 - 1);
                                    } else {
                                        verticesVector.push_back(verticesVector[temp4 - 1]);
                                        verticesVector[verticesVector.size() - 1].nx = normalsVector[temp5 - 1].x;
                                        verticesVector[verticesVector.size() - 1].ny = normalsVector[temp5 - 1].y;
                                        verticesVector[verticesVector.size() - 1].nz = normalsVector[temp5 - 1].z;
                                        verticesVector[verticesVector.size() - 1].nw = temp5 - 1;
                                        indicesVector.push_back(verticesVector.size() - 1);
                                    }
                                } else {
                                    indicesVector.push_back(temp4 - 1);
                                }
                            } else if (temp3.size() == 3) {
                                std::stringstream(temp3[0]) >> temp4;
                                if (!temp3[1].empty()) {
                                    std::stringstream(temp3[1]) >> temp5;
                                } else {
                                    temp5 = 0;
                                }
                                if (!temp3[2].empty()) {
                                    std::stringstream(temp3[2]) >> temp6;
                                } else {
                                    temp6 = 0;
                                }
                                if (std::round(verticesVector[temp4 - 1].nw) != temp6 - 1 || std::round(verticesVector[temp4 - 1].p) != temp5 - 1) {
                                    if (verticesVector[temp4 - 1].nw < 0 && verticesVector[temp4 - 1].p < 0) {
                                        verticesVector[temp4 - 1].nx = normalsVector[temp6 - 1].x;
                                        verticesVector[temp4 - 1].ny = normalsVector[temp6 - 1].y;
                                        verticesVector[temp4 - 1].nz = normalsVector[temp6 - 1].z;
                                        verticesVector[temp4 - 1].nw = temp6 - 1;
                                        verticesVector[temp4 - 1].u = texCoordsVector[temp5 - 1].x;
                                        verticesVector[temp4 - 1].v = texCoordsVector[temp5 - 1].y;
                                        verticesVector[temp4 - 1].w = texCoordsVector[temp5 - 1].z;
                                        verticesVector[temp4 - 1].p = temp5 - 1;
                                        indicesVector.push_back(temp4 - 1);
                                    } else {
                                        verticesVector.push_back(verticesVector[temp4 - 1]);
                                        verticesVector[verticesVector.size() - 1].nx = normalsVector[temp6 - 1].x;
                                        verticesVector[verticesVector.size() - 1].ny = normalsVector[temp6 - 1].y;
                                        verticesVector[verticesVector.size() - 1].nz = normalsVector[temp6 - 1].z;
                                        verticesVector[verticesVector.size() - 1].nw = temp6 - 1;
                                        verticesVector[verticesVector.size() - 1].u = texCoordsVector[temp5 - 1].x;
                                        verticesVector[verticesVector.size() - 1].v = texCoordsVector[temp5 - 1].y;
                                        verticesVector[verticesVector.size() - 1].w = texCoordsVector[temp5 - 1].z;
                                        verticesVector[verticesVector.size() - 1].p = temp5 - 1;
                                        indicesVector.push_back(verticesVector.size() - 1);
                                    }
                                } else {
                                    indicesVector.push_back(temp4 - 1);
                                }
                            }
                        }
                    }
                }
            }
            for (auto &i : verticesVector) {
                i.k = 1;
                i.nw = 0.0;
                i.p = 0.0;
            }

            return MeshRepresentation(verticesVector, indicesVector);
        }

        static const MeshRepresentation Cube;
        static const MeshRepresentation Icosahedron;

    };
}

#endif //COGL_MESHSKELETON_H

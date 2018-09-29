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
                output.k = std::stof(string_tokens[3]);
            }
        };

        static std::vector<cogl::MeshRepresentation> parse_obj(const std::vector<std::string> &objectCode) {
            std::vector<cogl::MeshRepresentation> objects_in_obj;

            auto first = std::find_if(objectCode.begin(), objectCode.end(), [&](const std::string& x){return cogl::utilities::begins_with(x, std::string("o "));});
			auto next = first;

            if (first == objectCode.end()) {
                first = objectCode.begin();
            }

			next = std::find_if(std::next(first, 1), objectCode.end(), [&](const std::string& x) {return cogl::utilities::begins_with(x, std::string("o ")); });

            while (first != next) {
                objects_in_obj.push_back(create_MeshRepresentation_from_obj(std::vector<std::string>(first, next)));
				first = next;
				if (first == objectCode.end()) break;
				next = std::find_if(std::next(first, 1), objectCode.end(), [&](const std::string& x) {return cogl::utilities::begins_with(x, std::string("o ")); });
            }

            return std::move(objects_in_obj);
        };

        static std::vector<cogl::Vertex> parse_vertices(const std::vector<std::string> &objectCode) {
            std::vector<Vertex> verticesVector;
			auto first_vertex_line = std::find_if(objectCode.begin(), objectCode.end(), [&](const auto &x) {return cogl::utilities::begins_with<std::string>(x, "v "); });
			auto last_vertex_line = std::find_if(objectCode.rbegin(), objectCode.rend(), [&](const auto &x) {return cogl::utilities::begins_with<std::string>(x, "v "); }).base();

			auto vertexCode = std::vector<std::string>(first_vertex_line, last_vertex_line);

			verticesVector.resize(vertexCode.size());

#pragma omp parallel for
			for (auto i = 0; i < vertexCode.size(); ++i) {
				Vertex temp{};
				temp.k = 1.0;
                set_to_split(std::string(std::next(vertexCode[i].begin(), 2), vertexCode[i].end()), " ", temp);
				temp.nw = 0;
				temp.p = 0;
                verticesVector[i] = temp;
            }

            return std::move(verticesVector);
        };

        static std::vector<glm::vec4> parse_normals(const std::vector<std::string> &objectCode) {
            std::vector<glm::vec4> normalsVector;

			auto first_normals_line = std::find_if(objectCode.begin(), objectCode.end(), [&](const auto &x) {return cogl::utilities::begins_with<std::string>(x, "vn "); });
			auto last_normals_line = std::find_if(objectCode.rbegin(), objectCode.rend(), [&](const auto &x) {return cogl::utilities::begins_with<std::string>(x, "vn "); }).base();

			if (first_normals_line != objectCode.end()) {
				auto normalsCode = std::vector<std::string>(first_normals_line, last_normals_line);

				if (normalsCode.size() > 0) {
					normalsVector.resize(normalsCode.size());
#pragma omp parallel for
					for (auto i = 0; i < normalsCode.size(); ++i) {
						glm::vec4 temp(0);
						set_to_split(std::string(std::next(normalsCode[i].begin(), 3), normalsCode[i].end()), " ", temp);
						normalsVector[i] = temp;
					}
				}
			}

            return std::move(normalsVector);
        }

        static std::vector<glm::vec4> parse_texture_coordinates(const std::vector<std::string> &objectCode) {
            std::vector<glm::vec4> texCoordsVector;

			auto first_texCoords_line = std::find_if(objectCode.begin(), objectCode.end(), [&](const auto &x) {return cogl::utilities::begins_with<std::string>(x, "vt "); });
			auto last_texCoords_line = std::find_if(objectCode.rbegin(), objectCode.rend(), [&](const auto &x) {return cogl::utilities::begins_with<std::string>(x, "vt "); }).base();

			if (first_texCoords_line != objectCode.end()) {
				auto texCoordsCode = std::vector<std::string>(first_texCoords_line, last_texCoords_line);

				if (texCoordsCode.size() > 0) {
					texCoordsVector.resize(texCoordsCode.size());
#pragma omp parallel for
					for (auto i = 0; i < texCoordsCode.size(); ++i) {
						glm::vec4 temp(0);
						set_to_split(std::string(std::next(texCoordsCode[i].begin(), 3), texCoordsCode[i].end()), " ", temp);
						texCoordsVector[i] = temp;
					}
				}
			}

            return std::move(texCoordsVector);
        }

		static std::vector<Face> parse_faces(const std::vector<std::string> &objectCode) {
			std::vector<Face> facesVector;
			glm::ivec3 temp2{ -1,-1,-1 };
			auto first_face_line = std::find_if(objectCode.begin(), objectCode.end(), [&](const auto &x) {return cogl::utilities::begins_with<std::string>(x, "f "); });
			auto last_face_line = std::find_if(objectCode.rbegin(), objectCode.rend(), [&](const auto &x) {return cogl::utilities::begins_with<std::string>(x, "f "); }).base();

			auto faceCode = std::vector<std::string>(first_face_line, last_face_line);

			facesVector.resize(faceCode.size());

			for (auto idx = 0; idx < faceCode.size(); ++idx) {
				auto line = faceCode[idx];
				Face tempFace;
				auto sanitized_line = cogl::utilities::split_string(line, " ", false);
				std::vector<decltype(sanitized_line)::value_type>(std::next(sanitized_line.begin(), 1), sanitized_line.end()).swap(sanitized_line);
				for (auto &vert : sanitized_line) {
					auto vertSplit = cogl::utilities::split_string(vert, "/", true);
					switch (vertSplit.size()) {
					case 1:
						temp2.x = std::stol(vertSplit[0]);
						break;
					case 2 :
						temp2.x = std::stol(vertSplit[0]);
						temp2.z = (vertSplit[1].empty() ? -1 : std::stol(vertSplit[1]));
						break;
					case 3:
						temp2.x = std::stoul(vertSplit[0]);
						temp2.z = (vertSplit[1].empty() ? -1 : std::stol(vertSplit[1]));
						temp2.y = (vertSplit[2].empty() ? -1 : std::stol(vertSplit[2]));
						break;
					}
					tempFace.faceVertices.push_back({ temp2.x, temp2.y, temp2.z });
				}
				facesVector[idx] = tempFace;
			}
			return std::move(facesVector);
		}

		static std::vector<Face> align_vertex_indices(const std::vector<Face> &faceVector) {
			auto min = std::numeric_limits<int>::max();
#pragma omp parallel
			{
				float min_local = min;
#pragma omp for nowait
				for (auto i = 1; i < faceVector.size(); i++) {
					for (auto j = 0; j < faceVector[j].faceVertices.size(); ++j) {
						if (faceVector[i].faceVertices[j].vertex_idx < min_local) {
							min_local = faceVector[i].faceVertices[j].vertex_idx;
						}
					}
				}
#pragma omp critical 
				{
					if (min_local < min) {
						min = min_local;
					}
				}
			}

			auto faceVectorCopy = faceVector;
#pragma omp parallel for
			for (auto i = 0; i < faceVectorCopy.size(); ++i) {
				for (auto j = 0; j < faceVectorCopy[i].faceVertices.size(); ++j) {
					faceVectorCopy[i].faceVertices[j].vertex_idx -= min;
				}
			}

			return std::move(faceVectorCopy);
		}


		static std::vector<Face> align_normal_indices(const std::vector<Face> &faceVector) {
			auto min = std::numeric_limits<int>::max();
#pragma omp parallel
			{
				float min_local = min;
#pragma omp for nowait
				for (auto i = 1; i < faceVector.size(); i++) {
					for (auto j = 0; j < faceVector[j].faceVertices.size(); ++j) {
						if (faceVector[i].faceVertices[j].normal_idx < min_local) {
							min_local = faceVector[i].faceVertices[j].normal_idx;
						}
					}
				}
#pragma omp critical 
				{
					if (min_local < min) {
						min = min_local;
					}
				}
			}

			auto faceVectorCopy = faceVector;
#pragma omp parallel for
			for (auto i = 0; i < faceVectorCopy.size(); ++i) {
				for (auto j = 0; j < faceVectorCopy[i].faceVertices.size(); ++j) {
					if (faceVectorCopy[i].faceVertices[j].normal_idx >= 0) faceVectorCopy[i].faceVertices[j].normal_idx -= min;
				}
			}

			return std::move(faceVectorCopy);
		}


		static std::vector<Face> align_texcoord_indices(const std::vector<Face> &faceVector) {
			auto min = std::numeric_limits<int>::max();
#pragma omp parallel
			{
				float min_local = min;
#pragma omp for nowait
				for (auto i = 1; i < faceVector.size(); i++) {
					for (auto j = 0; j < faceVector[j].faceVertices.size(); ++j) {
						if (faceVector[i].faceVertices[j].texcoord_idx < min_local) {
							min_local = faceVector[i].faceVertices[j].texcoord_idx;
						}
					}
				}
#pragma omp critical 
				{
					if (min_local < min) {
						min = min_local;
					}
				}
			}

			auto faceVectorCopy = faceVector;
#pragma omp parallel for
			for (auto i = 0; i < faceVectorCopy.size(); ++i) {
				for (auto j = 0; j < faceVectorCopy[i].faceVertices.size(); ++j) {
					if (faceVectorCopy[i].faceVertices[j].texcoord_idx >= 0) faceVectorCopy[i].faceVertices[j].texcoord_idx -= min;
				}
			}

			return std::move(faceVectorCopy);
		}

		static std::vector<Vertex> assign_nrm_texcoord_to_vertices(const std::vector<FaceVertex> &retVertices, const std::vector<glm::vec4> normalsVector, const std::vector<glm::vec4> texCoordsVector) {
			std::vector<Vertex> vertices;

			vertices.resize(retVertices.size());
#pragma omp parallel for
			for (auto i = 0; i < vertices.size(); ++i) {
				vertices[i] = retVertices[i].faceVertex;
				if (retVertices[i].faceVertexIndices.normal_idx >= 0) {
					auto local_normal = normalsVector[retVertices[i].faceVertexIndices.normal_idx];
					local_normal /= glm::length(local_normal);
					vertices[i].nx = local_normal.x;
					vertices[i].ny = local_normal.y;
					vertices[i].nz = local_normal.z;
					vertices[i].nw = local_normal.w;
				}
				if (retVertices[i].faceVertexIndices.texcoord_idx >= 0) {
					auto local_texcoords = texCoordsVector[retVertices[i].faceVertexIndices.texcoord_idx];
					vertices[i].u = local_texcoords.x;
					vertices[i].v = local_texcoords.y;
					vertices[i].w = local_texcoords.z;
					vertices[i].p = local_texcoords.w;
				}
			}

			return std::move(vertices);
		}

		inline static glm::vec4 normal_to_plane(const glm::vec4 &a, const glm::vec4 &b, const glm::vec4 &c, const glm::vec4 &d) {
			return glm::vec4(glm::cross(glm::vec3(c - a), glm::vec3(d - b)), 0.0);
		}

        static MeshRepresentation create_MeshRepresentation_from_obj(const std::vector<std::string> &objectCode) {
            std::vector<unsigned int> retIndices;

			auto verticesVector = parse_vertices(objectCode);
			auto normalsVector = parse_normals(objectCode);
			auto texCoordsVector = parse_texture_coordinates(objectCode);
			auto facesVector = parse_faces(objectCode);
			facesVector = align_normal_indices(align_texcoord_indices(align_vertex_indices(facesVector)));

			std::vector<FaceVertex> retVertices;
			retVertices.resize(verticesVector.size());
#pragma omp parallel for
			for (auto i = 0; i < verticesVector.size(); ++i) {
				retVertices[i] = { verticesVector[i], {i, -1, -1} };
			}

			for (auto &i : facesVector) {
				switch (i.faceVertices.size()) {
				case 3:
					for (auto &idx : i.faceVertices) {
						if ((retVertices[idx.vertex_idx].faceVertexIndices.normal_idx != -1 && idx.normal_idx != retVertices[idx.vertex_idx].faceVertexIndices.normal_idx) ||
							(retVertices[idx.vertex_idx].faceVertexIndices.texcoord_idx != -1 && idx.texcoord_idx != retVertices[idx.vertex_idx].faceVertexIndices.texcoord_idx)) {
							retVertices.push_back(retVertices[idx.vertex_idx]);
							retVertices.back().faceVertexIndices = { static_cast<int>(retVertices.size() - 1), static_cast<int>(idx.normal_idx), static_cast<int>(idx.texcoord_idx)};
							retIndices.push_back(retVertices.size() - 1);
						} else {
							retVertices[idx.vertex_idx].faceVertexIndices = { static_cast<int>(idx.vertex_idx),  static_cast<int>(idx.normal_idx), static_cast<int>(idx.texcoord_idx) };
							retIndices.push_back(idx.vertex_idx);
						}
					}

					auto curr_face_indices = std::vector<unsigned int>(std::prev(retIndices.end(), 3), retIndices.end());

					for (auto idx = 0; idx < curr_face_indices.size(); ++idx) {
						Vertex a, b, c;

						a = retVertices[curr_face_indices[0]].faceVertex;
						b = retVertices[curr_face_indices[1]].faceVertex;
						c = retVertices[curr_face_indices[2]].faceVertex;

						auto currNormal = normal_to_plane(glm::vec4(a.x, a.y, a.z, a.k), glm::vec4(a.x, a.y, a.z, a.k), glm::vec4(b.x, b.y, b.z, b.k), glm::vec4(c.x, c.y, c.z, c.k));

						if (retVertices[curr_face_indices[idx]].faceVertexIndices.normal_idx == -1) {
							normalsVector.push_back(currNormal);
							retVertices[curr_face_indices[idx]].faceVertexIndices.normal_idx = normalsVector.size() - 1;
						} else {
							normalsVector[retVertices[curr_face_indices[idx]].faceVertexIndices.normal_idx] += currNormal;
						}
					}

					break;
				}
			}

            return std::move(MeshRepresentation(assign_nrm_texcoord_to_vertices(retVertices, normalsVector, texCoordsVector), retIndices));
        }

        static std::vector<MeshRepresentation> load_from_obj(const std::string &obj_filepath) {
            return std::move(parse_obj(cogl::utilities::read_text_to_vector(obj_filepath)));
        }

        static const MeshRepresentation Cube;
        static const MeshRepresentation Icosahedron;

    };
}

#endif //COGL_MESHSKELETON_H

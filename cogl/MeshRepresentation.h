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

        static MeshRepresentation load_from_obj(const std::string &filename) {
            std::vector<Vertex> verticesVector;
            std::vector<unsigned int> indicesVector;

            // Read the Vertex Shader code from the file
            std::vector<std::string> objectCode;
            std::ifstream objectStream(filename, std::ios::in);
            if (objectStream.is_open()) {
                std::string Line;
                while (getline(objectStream, Line))
                    objectCode.emplace_back(Line);
                objectStream.close();
            } else {
                printf("Impossible to open %s. Are you in the right directory?\n", filename);
                getchar();
            }

            for (auto &i : objectCode) {
                if (i[0] == 'v') {
                    std::stringstream temp(i);
                    Vertex temp2{};
                    char throwaway;
                    temp >> throwaway;
                    temp >> temp2.x;
                    temp >> temp2.y;
                    temp >> temp2.z;
                    verticesVector.push_back(temp2);
                } else if (i[0] == 'f') {
                    std::stringstream temp(i);
                    unsigned int temp2;
                    char throwaway;
                    temp >> throwaway;
                    temp >> temp2;
                    indicesVector.push_back(temp2 - 1);
                    temp >> temp2;
                    indicesVector.push_back(temp2 - 1);
                    temp >> temp2;
                    indicesVector.push_back(temp2 - 1);
                }
            }

            return MeshRepresentation(verticesVector, indicesVector);
        }

        static const MeshRepresentation Cube;
        static const MeshRepresentation Icosahedron;

    };
}

#endif //COGL_MESHSKELETON_H

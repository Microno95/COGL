//
// Created by ekin4 on 23/02/2017.
//

#ifndef IDEK_MESHES_H
#define IDEK_MESHES_H

#include "Renderable.h"

namespace cogl {
    class Mesh : public Renderable {
    private:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        glm::mat4x4 rotMatrix, transMatrix, scaleMatrix, normalMatrix;
        RenderTypes renderType;

    protected:
        bool VAO_initialised = false;
        GLuint VAO, vertexBuffer, indexBuffer;
    public:

        Mesh();

        Mesh(const Mesh &other);

        Mesh(const std::vector<Vertex> &verticesInit);

        Mesh(const std::vector<Vertex> &verticesInit, const std::vector<unsigned int> &indicesInit,
             RenderTypes rType = RenderTypes::Tris);

        //Move Constructor
        Mesh(Mesh &&other);

        // Move Assignment
        Mesh &operator=(Mesh &&other);

        // Copy Assignment
        Mesh &operator=(const Mesh &other);

        // Destructor
        ~Mesh();

        void initialiseVAO();

        void clearVAO();

        void render(const Shader &program, const Camera &renderCamera);

        void rotateMesh(const double angle, const glm::vec3 axisOfRotation);

        void scaleMesh(const double xScale, const double yScale, const double zScale);

        void scaleMesh(const double &scale) { this->scaleMesh(scale, scale, scale); };

        void moveMesh(const glm::vec3 translation);

        void moveMeshTo(const glm::vec3 translation);

        void setRenderType(const RenderTypes rType);

        const RenderTypes getRenderType();

        const glm::mat4x4 getModelMatrix() const;

        const glm::mat4x4 getNormalMatrix() const;

        const glm::mat4x4 getTransMatrix() const;

        const glm::mat4x4 getRotMatrix() const;

        const glm::mat4x4 getScaleMatrix() const;

        // Default Shapes //
        static const Mesh Cube;
        static const Mesh Icosahedron;
        // -------------- //

        friend std::ostream &operator<<(std::ostream &outstream, const Mesh &rhs) {
            for (auto i = 0; i < rhs.vertices.size(); ++i) {
                std::cout << "Vertex " << i << ":" << std::endl << rhs.vertices[i] << std::endl;
            }
            for (auto i : rhs.indices) std::cout << i << ", ";
            std::cout << std::endl;
            std::cout << glm::to_string(rhs.getModelMatrix()) << std::endl;
            return outstream;
        }

        static Mesh load_from_obj(const std::string filename);
    };

}
#endif //IDEK_MESHES_H

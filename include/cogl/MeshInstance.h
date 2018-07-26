//
// Created by ekin4 on 28/02/2017.
//

#ifndef IDEK_MESHINSTANCED_H
#define IDEK_MESHINSTANCED_H

#include "Renderable.h"
#include "Mesh.h"

/*
 * Generic class to store a set of renderable meshes that share the same vertex structure but located at
 * different positions/rotations/scalings. The purpose is to increase rendering speed when the same mesh is
 * rendered multiple times using the same shader.
 * */

namespace cogl {
    class MeshInstance : public Renderable {
    private:
        MeshRepresentation meshRepr;
        std::vector<glm::mat4x4> rotMatrix, transMatrix, scaleMatrix, modelMatrix;
        RenderTypes renderType = RenderTypes::Points;

        void removeInstanceHelper(size_t objectID);

        void initialiseVAO();

    protected:
        bool VAO_initialised = false;
        GLuint transformBuffer = 0, vertexBuffer = 0, indexBuffer = 0;
        GLuint VAO = 0;

    public:

        MeshInstance(const MeshInstance &other)=delete;

        MeshInstance(const std::vector<Vertex> &verticesInit, const std::vector<unsigned int> &indicesInit,
                     unsigned int numCopies, RenderTypes rType = RenderTypes::Tris);

        MeshInstance(const std::vector<Vertex> &verticesInit, const std::vector<unsigned int> &indicesInit,
                     const std::vector<glm::mat4x4> &transformMatrices, RenderTypes rType = RenderTypes::Tris);

        MeshInstance(const Mesh &other, std::size_t numCopies);

        MeshInstance(MeshRepresentation other, std::size_t numCopies);

        //Move Constructor
        MeshInstance(MeshInstance &&other) noexcept;

        // Move Assignment
        MeshInstance &operator=(MeshInstance &&other) noexcept;

        // Copy Assignment
        MeshInstance &operator=(const MeshInstance &other)=delete;

        ~MeshInstance();

        void release();

        void render(const Shader &program, const Camera &renderCamera, bool update_gpu_data) override;

        void rotateMesh(int objectID, const double &angle, const glm::vec3 &axisOfRotation);

        void scaleMesh(int objectID, const double &xScale, const double &yScale, const double &zScale);

        void scaleMesh(const int objectID, const double &scale) { this->scaleMesh(objectID, scale, scale, scale); };

        void moveMesh(int objectID, const glm::vec3 &translation);

        void moveMeshTo(int objectID, const glm::vec3 &translation);

        void moveMeshTo(const std::vector<glm::vec3> &translation);

        void setRenderType(const RenderTypes &rType);

        const RenderTypes &getRenderType() const;

        const glm::mat4x4 &getModelMatrix(int objectID) const;

        const glm::mat4x4 &getTransMatrix(int objectID) const;

        const glm::mat4x4 &getRotMatrix(int objectID) const;

        const glm::mat4x4 &getScaleMatrix(int objectID) const;

        const std::vector<glm::mat4x4> &getModelMatrix() const;

        const std::vector<glm::mat4x4> &getTransMatrix() const;

        const std::vector<glm::mat4x4> &getRotMatrix() const;

        const std::vector<glm::mat4x4> &getScaleMatrix() const;

        void addInstance();

        void addInstance(const glm::mat4x4 &transform,
                         const glm::mat4x4 &rotation,
                         const glm::mat4x4 &scale);

        void addInstances(const std::vector<glm::mat4x4> &transforms,
                          const std::vector<glm::mat4x4> &rotations,
                          const std::vector<glm::mat4x4> &scales);

        void addInstance(const glm::mat4x4 &modelMatrix);

        void addInstances(const std::vector<glm::mat4x4> &modelMatrices);

        void removeInstance(size_t objectID);

        void removeInstances(std::vector<size_t> objectID);

        unsigned long long activeInstances() const {
            return modelMatrix.size();
        };

        const MeshRepresentation getMeshRepresentation() const;
    };

}
#endif //IDEK_MESHINSTANCED_H

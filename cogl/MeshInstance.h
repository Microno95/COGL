//
// Created by ekin4 on 28/02/2017.
//

#ifndef IDEK_MESHINSTANCED_H
#define IDEK_MESHINSTANCED_H

#include "Renderable.h"

namespace cogl {
    class MeshInstance : public Renderable {
    private:
        static const unsigned int SUBDIVIDE_UPDATE_MESH_COUNT = 250000;
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<bool> changedMatrices;
        std::vector<glm::mat4x4> rotMatrix, transMatrix, scaleMatrix, normalMatrix, modelMatrix;
        RenderTypes renderType = RenderTypes::Points;

        void removeInstanceHelper(const unsigned long long objectID);

    protected:
        bool VAO_initialised = false;
        GLuint transformBuffer, normalBuffer;
        GLuint VAO;
    public:

        MeshInstance();

        MeshInstance(const MeshInstance &other);

        MeshInstance(const std::vector<Vertex> &verticesInit,
                     RenderTypes rType = RenderTypes::Tris);

        MeshInstance(const std::vector<Vertex> &verticesInit, const std::vector<unsigned int> &indicesInit,
                     RenderTypes rType = RenderTypes::Tris);

        MeshInstance(const std::vector<Vertex> &verticesInit, const std::vector<unsigned int> &indicesInit,
                     const std::vector<glm::mat4x4> &transformMatrices, RenderTypes rType = RenderTypes::Tris);

        //Move Constructor
        MeshInstance(MeshInstance &&other);

        // Move Assignment
        MeshInstance &operator=(MeshInstance &&other);

        // Copy Assignment
        MeshInstance &operator=(const MeshInstance &other);

        ~MeshInstance();

        void initialiseVAO();

        void clearVAO();

        void render(const Shader &program, const Camera &renderCamera);

        void rotateMesh(const int objectID, const double &angle, const glm::vec3 &axisOfRotation);

        void scaleMesh(const int objectID, const double &xScale, const double &yScale, const double &zScale);

        void scaleMesh(const int objectID, const double &scale) { this->scaleMesh(objectID, scale, scale, scale); };

        void moveMesh(const int objectID, const glm::vec3 &translation);

        void moveMeshTo(const int objectID, const glm::vec3 &translation);

        void moveMeshTo(const std::vector<glm::vec3> &translation);

        void setRenderType(const RenderTypes &rType);

        const RenderTypes &getRenderType() const;

        const glm::mat4x4 &getModelMatrix(const int objectID) const;

        const glm::mat4x4 &getNormalMatrix(const int objectID) const;

        const glm::mat4x4 &getTransMatrix(const int objectID) const;

        const glm::mat4x4 &getRotMatrix(const int objectID) const;

        const glm::mat4x4 &getScaleMatrix(const int objectID) const;

        const std::vector<glm::mat4x4> &getModelMatrix() const;

        const std::vector<glm::mat4x4> &getNormalMatrix() const;

        const std::vector<glm::mat4x4> &getTransMatrix() const;

        const std::vector<glm::mat4x4> &getRotMatrix() const;

        const std::vector<glm::mat4x4> &getScaleMatrix() const;

        void addInstance(const glm::mat4x4 &transform,
                         const glm::mat4x4 &rotation,
                         const glm::mat4x4 &scale);

        void addInstances(const std::vector<glm::mat4x4> &transforms,
                          const std::vector<glm::mat4x4> &rotations,
                          const std::vector<glm::mat4x4> &scales);

        void addInstance(const glm::mat4x4 &modelMatrix);

        void addInstances(const std::vector<glm::mat4x4> &modelMatrices);

        void removeInstance(const unsigned long long objectID);

        void removeInstances(const std::vector<unsigned long long> objectID);

        unsigned long long activeInstances() { return modelMatrix.size(); };
    };

}
#endif //IDEK_MESHINSTANCED_H

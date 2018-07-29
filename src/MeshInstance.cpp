//
// Created by ekin4 on 28/02/2017.
//

#include "cogl/MeshInstance.h"

namespace cogl {
    MeshInstance::MeshInstance(const std::vector<Vertex> &verticesInit, const std::vector<unsigned int> &indicesInit, unsigned int numCopies, RenderTypes rType) : meshRepr(verticesInit, indicesInit){
        rotMatrix = std::vector<glm::mat4x4>(numCopies, glm::mat4x4(1.0f));
        transMatrix = std::vector<glm::mat4x4>(numCopies, glm::mat4x4(1.0f));
        scaleMatrix = std::vector<glm::mat4x4>(numCopies, glm::mat4x4(1.0f));
        modelMatrix = std::vector<glm::mat4x4>(numCopies, glm::mat4x4(1.0f));
        renderType = rType;

        initialiseVAO();
    }
    MeshInstance::MeshInstance(const std::vector<Vertex> &verticesInit, const std::vector<unsigned int> &indicesInit,
                               const std::vector<glm::mat4x4> &transformMatrices, RenderTypes rType) : meshRepr(verticesInit, indicesInit) {
        renderType = rType;
        rotMatrix = std::vector<glm::mat4x4>();
        rotMatrix.reserve(transformMatrices.size());
        scaleMatrix = std::vector<glm::mat4x4>();
        scaleMatrix.reserve(transformMatrices.size());
        transMatrix = std::vector<glm::mat4x4>();
        transMatrix.reserve(transformMatrices.size());
        modelMatrix = std::vector<glm::mat4x4>(transformMatrices);
        for (auto &i : transformMatrices) {
            transMatrix.emplace_back(1.0f);
            rotMatrix.push_back(glm::extractMatrixRotation(i));
            transMatrix.back()[3] = i[3] / i[3][3];
            scaleMatrix.push_back(glm::inverse(rotMatrix.back()) * glm::inverse(transMatrix.back()) * i);
        }

        initialiseVAO();
    }

    MeshInstance::MeshInstance(const Mesh &other, const std::size_t numCopies) : meshRepr(std::move(other.getMeshRepresentation())){
        rotMatrix = std::vector<glm::mat4x4>(numCopies, other.getRotMatrix());
        transMatrix = std::vector<glm::mat4x4>(numCopies, other.getTransMatrix());
        scaleMatrix = std::vector<glm::mat4x4>(numCopies, other.getScaleMatrix());
        modelMatrix = std::vector<glm::mat4x4>(numCopies, other.getModelMatrix());
        renderType = other.getRenderType();

        initialiseVAO();
    }

    MeshInstance::MeshInstance(MeshRepresentation other, const std::size_t numCopies) : meshRepr(std::move(other)){
        rotMatrix = std::vector<glm::mat4x4>(numCopies, glm::mat4x4(1.0f));
        transMatrix = std::vector<glm::mat4x4>(numCopies, glm::mat4x4(1.0f));
        scaleMatrix = std::vector<glm::mat4x4>(numCopies, glm::mat4x4(1.0f));
        modelMatrix = std::vector<glm::mat4x4>(numCopies, glm::mat4x4(1.0f));
        renderType = cogl::RenderTypes::Tris;

        initialiseVAO();
    }

    MeshInstance::MeshInstance(MeshInstance &&other) noexcept : VAO(other.VAO), indexBuffer(other.indexBuffer),
                                                                vertexBuffer(other.vertexBuffer), transformBuffer(other.transformBuffer),
                                                                meshRepr(other.meshRepr),rotMatrix(other.rotMatrix),transMatrix(other.transMatrix),
                                                                scaleMatrix(other.scaleMatrix),renderType(other.renderType){
        other.VAO = 0;
        other.indexBuffer = 0;
        other.vertexBuffer = 0;
        other.transformBuffer = 0;
    }

    MeshInstance &MeshInstance::operator=(MeshInstance &&other) noexcept {
        if (this != &other) {
            release();
            std::swap(this->VAO, other.VAO);
            std::swap(this->transformBuffer, other.transformBuffer);
            std::swap(this->VAO_initialised, other.VAO_initialised);
            std::swap(this->meshRepr, other.meshRepr);
            std::swap(this->rotMatrix, other.rotMatrix);
            std::swap(this->transMatrix, other.transMatrix);
            std::swap(this->scaleMatrix, other.scaleMatrix);
            std::swap(this->modelMatrix, other.modelMatrix);
            std::swap(this->renderType, other.renderType);
        }
		return *this;
    }

    MeshInstance::~MeshInstance() {
        release();
    }

    void MeshInstance::release() {
        glDeleteBuffers(1, &vertexBuffer);
        glDeleteBuffers(1, &indexBuffer);
        glDeleteBuffers(1, &transformBuffer);
        glDeleteVertexArrays(1, &VAO);
    }

    void MeshInstance::render(const Shader &program, const Camera &renderCamera, bool update_gpu_data) {
        program.bind();
        glm::mat4x4 temp1;
		if (program.getUniformLoc("vp") != -1) {
			temp1 = renderCamera.getVPMatrix();
			glUniformMatrix4fv(program.getUniformLoc("vp"), 1, GL_FALSE, (const GLfloat *)&temp1);
		};

        glBindVertexArray(VAO);

        if (update_gpu_data) {
            glNamedBufferSubData(transformBuffer, 0, modelMatrix.size() * sizeof(glm::mat4x4),
                                 (GLvoid * ) &modelMatrix.front());
        }

        glDrawElementsInstanced(renderType, (GLsizei) meshRepr.indices.size(), GL_UNSIGNED_INT, 0,
                                (GLsizei) modelMatrix.size());
		check_gl_error();

        glBindVertexArray(0);
        cogl::Shader::unbind();
    }

    void MeshInstance::rotateMesh(const int objectID, const double &angle, const glm::vec3 &axisOfRotation) {
        if (objectID == -1) {
#pragma omp parallel for
            for (auto i = 0; i < rotMatrix.size(); ++i) {
                rotMatrix[i] = glm::rotate((float) angle, axisOfRotation) * rotMatrix[i];
                if (renderType != RenderTypes::Points) {
                    modelMatrix[i] = transMatrix[i] * rotMatrix[i] * scaleMatrix[i];
                } else {
                    modelMatrix[i] = transMatrix[i];
                }
            }
        } else {
            rotMatrix[objectID] = glm::rotate((float) angle, axisOfRotation) * rotMatrix[objectID];
            modelMatrix[objectID] = transMatrix[objectID] * rotMatrix[objectID] * scaleMatrix[objectID];
        }
    }

    void MeshInstance::scaleMesh(const int objectID, const double &xScale, const double &yScale, const double &zScale) {
        if (objectID == -1) {
#pragma omp parallel for
            for (auto i = 0; i < rotMatrix.size(); ++i) {
                scaleMatrix[i] = glm::scale(glm::vec3({xScale, yScale, zScale})) * scaleMatrix[i];
                if (renderType != RenderTypes::Points) {
                    modelMatrix[i] = transMatrix[i] * rotMatrix[i] * scaleMatrix[i];
                } else {
                    modelMatrix[i] = transMatrix[i];
                }
            }
        } else {
            scaleMatrix[objectID] = glm::scale(glm::vec3({xScale, yScale, zScale})) * scaleMatrix[objectID];
            modelMatrix[objectID] = transMatrix[objectID] * rotMatrix[objectID] * scaleMatrix[objectID];
        }
    }

    void MeshInstance::moveMesh(const int objectID, const glm::vec3 &translation) {
        if (objectID == -1) {
#pragma omp parallel for
            for (auto i = 0; i < rotMatrix.size(); ++i) {
                transMatrix[i] = glm::translate(translation) * transMatrix[i];
                if (renderType != RenderTypes::Points) {
                    modelMatrix[i] = transMatrix[i] * rotMatrix[i] * scaleMatrix[i];
                } else {
                    modelMatrix[i] = transMatrix[i];
                }
            }
        } else {
            transMatrix[objectID] = glm::translate(translation) * transMatrix[objectID];
            modelMatrix[objectID] = transMatrix[objectID] * rotMatrix[objectID] * scaleMatrix[objectID];
        }
    }

    void MeshInstance::moveMeshTo(const int objectID, const glm::vec3 &translation) {
        if (objectID == -1) {
#pragma omp parallel for
            for (auto i = 0; i < transMatrix.size(); ++i) {
                transMatrix[i] = glm::translate(glm::mat4x4(1.0f), translation);
                if (renderType != RenderTypes::Points) {
                    modelMatrix[i] = transMatrix[i] * rotMatrix[i] * scaleMatrix[i];
                } else {
                    modelMatrix[i] = transMatrix[i];
                }
            }
        } else {
            transMatrix[objectID] = glm::translate(glm::mat4x4(1.0f), translation);
            modelMatrix[objectID] = transMatrix[objectID] * rotMatrix[objectID] * scaleMatrix[objectID];
        }
    }

    void MeshInstance::moveMeshTo(const std::vector<glm::vec3> &translation) {
#pragma omp parallel for
        for (auto i = 0; i < translation.size(); ++i) {
            transMatrix[i] = glm::translate(glm::mat4x4(1.0f), translation[i]);
            if (renderType != RenderTypes::Points) {
                modelMatrix[i] = transMatrix[i] * rotMatrix[i] * scaleMatrix[i];
            } else {
                modelMatrix[i] = transMatrix[i];
            }
        }
    }

    void MeshInstance::setRenderType(const RenderTypes &rType) {
        renderType = rType;
    }

    const RenderTypes &MeshInstance::getRenderType() const {
        return renderType;
    }

    const glm::mat4x4 &MeshInstance::getModelMatrix(const int objectID) const {
        return modelMatrix[objectID];
    }

    const glm::mat4x4 &MeshInstance::getTransMatrix(const int objectID) const {
        return transMatrix[objectID];
    }

    const glm::mat4x4 &MeshInstance::getRotMatrix(const int objectID) const {
        return rotMatrix[objectID];
    }

    const glm::mat4x4 &MeshInstance::getScaleMatrix(const int objectID) const {
        return scaleMatrix[objectID];
    }

    const std::vector<glm::mat4x4> &MeshInstance::getModelMatrix() const {
        return modelMatrix;
    }

    const std::vector<glm::mat4x4> &MeshInstance::getTransMatrix() const {
        return transMatrix;
    }

    const std::vector<glm::mat4x4> &MeshInstance::getRotMatrix() const {
        return rotMatrix;
    }

    const std::vector<glm::mat4x4> &MeshInstance::getScaleMatrix() const {
        return scaleMatrix;
    }

    void
    MeshInstance::addInstance() {
        transMatrix.emplace_back();
        rotMatrix.emplace_back(1.0f);
        scaleMatrix.emplace_back(1.0f);
        modelMatrix.emplace_back(1.0f);
        release();
        initialiseVAO();
    }

    void
    MeshInstance::addInstance(const glm::mat4x4 &transform, const glm::mat4x4 &rotation, const glm::mat4x4 &scale) {
        transMatrix.push_back(transform);
        rotMatrix.push_back(rotation);
        scaleMatrix.push_back(scale);
        modelMatrix.push_back(transform * rotation * scale);
        release();
        initialiseVAO();
    }

    void
    MeshInstance::addInstances(const std::vector<glm::mat4x4> &transforms, const std::vector<glm::mat4x4> &rotations,
                               const std::vector<glm::mat4x4> &scales) {
        for (size_t i = 0; i < transforms.size(); ++i) {
            transMatrix.push_back(transforms[i]);
            rotMatrix.push_back(rotations[i]);
            scaleMatrix.push_back(scales[i]);
            modelMatrix.push_back(transforms[i] * rotations[i] * scales[i]);
            addInstance(transforms[i], rotations[i], scales[i]);
        }
        release();
        initialiseVAO();
    }

    void MeshInstance::addInstance(const glm::mat4x4 &modelMatrix) {
        transMatrix.emplace_back(1.0f);
        rotMatrix.push_back(glm::extractMatrixRotation(modelMatrix));
        transMatrix.back()[3] = modelMatrix[3] / modelMatrix[3][3];
        scaleMatrix.push_back(glm::inverse(rotMatrix.back()) * glm::inverse(transMatrix.back()) * modelMatrix);
        this->modelMatrix.push_back(transMatrix.back() * rotMatrix.back() * scaleMatrix.back());
        release();
        initialiseVAO();
    }

    void MeshInstance::addInstances(const std::vector<glm::mat4x4> &modelMatrices) {
        for (auto i : modelMatrices) addInstance(i);
    }

    void MeshInstance::removeInstanceHelper(const size_t objectID) {
        if (objectID < transMatrix.size()) {
            transMatrix.erase(transMatrix.begin() + objectID);
            rotMatrix.erase(rotMatrix.begin() + objectID);
            scaleMatrix.erase(scaleMatrix.begin() + objectID);
        }
    }

    void MeshInstance::removeInstance(const size_t objectID) {
        if (objectID < transMatrix.size()) {
            removeInstanceHelper(objectID);
            release();
            initialiseVAO();
        }
    }

    void MeshInstance::removeInstances(const std::vector<size_t> objectID) {
        for (auto &&i : objectID) {
            if (i < transMatrix.size()) removeInstanceHelper(i);
        }
        release();
        initialiseVAO();
    }

    void MeshInstance::initialiseVAO() {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &vertexBuffer);
        glGenBuffers(1, &indexBuffer);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, meshRepr.vertices.size() * sizeof(Vertex), &meshRepr.vertices.front(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid * ) 0); // Position Vector

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (sizeof(float) * 3)); // Normal Vector

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (sizeof(float) * 6)); // RGBA Values

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (sizeof(float) * 10)); // UV Coords

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshRepr.indices.size() * sizeof(unsigned int), &meshRepr.indices.front(), GL_STATIC_DRAW);

        glGenBuffers(1, &transformBuffer);

        glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
        glBufferData(GL_ARRAY_BUFFER, modelMatrix.size() * sizeof(glm::mat4x4), (GLvoid *) &(modelMatrix.front()),
                     GL_STREAM_DRAW);

        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (GLvoid *) 0);
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (GLvoid *) (sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (GLvoid *) (sizeof(glm::vec4) * 2));
        glEnableVertexAttribArray(7);
        glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (GLvoid *) (sizeof(glm::vec4) * 3));

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glVertexAttribDivisor(0, 0);
        glVertexAttribDivisor(1, 0);
        glVertexAttribDivisor(2, 0);
        glVertexAttribDivisor(3, 0);

        for (GLuint i = 4; i <= 7; ++i) glVertexAttribDivisor(i, 1);

        glBindVertexArray(0);
    }

    const MeshRepresentation MeshInstance::getMeshRepresentation() const {
        return MeshRepresentation(this->meshRepr);
    }
}

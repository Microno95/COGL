//
// Created by ekin4 on 28/02/2017.
//

#include "MeshInstance.h"

namespace cogl {
    MeshInstance::MeshInstance() {
        vertices = std::vector<Vertex>();
        indices = std::vector<unsigned int>();
        rotMatrix = std::vector<glm::mat4x4>();
        rotMatrix.reserve(25);
        scaleMatrix = std::vector<glm::mat4x4>();
        scaleMatrix.reserve(25);
        transMatrix = std::vector<glm::mat4x4>();
        transMatrix.reserve(25);
        modelMatrix = std::vector<glm::mat4x4>();
        modelMatrix.reserve(25);
    }

    MeshInstance::MeshInstance(const MeshInstance &other) {
        vertices = other.vertices;
        indices = other.indices;
        rotMatrix = other.rotMatrix;
        transMatrix = other.transMatrix;
        scaleMatrix = other.scaleMatrix;
        modelMatrix = other.modelMatrix;
    }

    MeshInstance::MeshInstance(const std::vector<Vertex> &verticesInit,
                               RenderTypes rType) {
        renderType = rType;
        vertices = std::vector<Vertex>(verticesInit);
        indices = std::vector<unsigned int>();
        for (unsigned int i = 0; i < vertices.size(); i++) indices.push_back(i);
        rotMatrix = std::vector<glm::mat4x4>();
        rotMatrix.reserve(25);
        scaleMatrix = std::vector<glm::mat4x4>();
        scaleMatrix.reserve(25);
        transMatrix = std::vector<glm::mat4x4>();
        transMatrix.reserve(25);
        modelMatrix = std::vector<glm::mat4x4>();
        modelMatrix.reserve(25);
        rotMatrix.emplace_back(1.0f);
        transMatrix.emplace_back(1.0f);
        scaleMatrix.emplace_back(1.0f);
        modelMatrix.emplace_back(1.0f);
    }

    MeshInstance::MeshInstance(const std::vector<Vertex> &verticesInit, const std::vector<unsigned int> &indicesInit,
                               RenderTypes rType) {
        vertices = std::vector<Vertex>(verticesInit);
        indices = std::vector<unsigned int>(indicesInit);
        renderType = rType;
        rotMatrix = std::vector<glm::mat4x4>();
        rotMatrix.reserve(25);
        scaleMatrix = std::vector<glm::mat4x4>();
        scaleMatrix.reserve(25);
        transMatrix = std::vector<glm::mat4x4>();
        transMatrix.reserve(25);
        modelMatrix = std::vector<glm::mat4x4>();
        modelMatrix.reserve(25);
        rotMatrix.emplace_back(1.0f);
        transMatrix.emplace_back(1.0f);
        scaleMatrix.emplace_back(1.0f);
        modelMatrix.emplace_back(1.0f);
    }

    MeshInstance::MeshInstance(const std::vector<Vertex> &verticesInit, const std::vector<unsigned int> &indicesInit,
                               const std::vector<glm::mat4x4> &transformMatrices, RenderTypes rType) {
        vertices = std::vector<Vertex>(verticesInit);
        indices = std::vector<unsigned int>(indicesInit);
        renderType = rType;
        rotMatrix = std::vector<glm::mat4x4>();
        rotMatrix.reserve(transformMatrices.size());
        scaleMatrix = std::vector<glm::mat4x4>();
        scaleMatrix.reserve(transformMatrices.size());
        transMatrix = std::vector<glm::mat4x4>();
        transMatrix.reserve(transformMatrices.size());
        modelMatrix = std::vector<glm::mat4x4>();
        modelMatrix.reserve(transformMatrices.size());
        modelMatrix = std::vector<glm::mat4x4>(transformMatrices);
        for (auto &i : transformMatrices) {
            transMatrix.emplace_back(1.0f);
            rotMatrix.push_back(glm::extractMatrixRotation(i));
            transMatrix.back()[3] = i[3] / i[3][3];
            scaleMatrix.push_back(glm::inverse(rotMatrix.back()) * glm::inverse(transMatrix.back()) * i);
        }
    }

    MeshInstance::MeshInstance(const Mesh &other, const std::size_t numCopies) {
        vertices = other.getVertices();
        indices = other.getIndices();
        rotMatrix = std::vector<glm::mat4x4>(numCopies, other.getRotMatrix());
        transMatrix = std::vector<glm::mat4x4>(numCopies, other.getTransMatrix());
        scaleMatrix = std::vector<glm::mat4x4>(numCopies, other.getScaleMatrix());
        modelMatrix = std::vector<glm::mat4x4>(numCopies, other.getModelMatrix());
        renderType = other.getRenderType();
    }

    MeshInstance::MeshInstance(MeshInstance &&other) noexcept {
        std::swap(this->VAO, other.VAO);
        std::swap(this->transformBuffer, other.transformBuffer);
        std::swap(this->VAO_initialised, other.VAO_initialised);
        std::swap(this->vertices, other.vertices);
        std::swap(this->indices, other.indices);
        std::swap(this->rotMatrix, other.rotMatrix);
        std::swap(this->transMatrix, other.transMatrix);
        std::swap(this->scaleMatrix, other.scaleMatrix);
        std::swap(this->renderType, other.renderType);
    }

    MeshInstance &MeshInstance::operator=(MeshInstance &&other) {
        std::swap(this->VAO, other.VAO);
        std::swap(this->transformBuffer, other.transformBuffer);
        std::swap(this->VAO_initialised, other.VAO_initialised);
        std::swap(this->vertices, other.vertices);
        std::swap(this->indices, other.indices);
        std::swap(this->rotMatrix, other.rotMatrix);
        std::swap(this->transMatrix, other.transMatrix);
        std::swap(this->scaleMatrix, other.scaleMatrix);
        std::swap(this->renderType, other.renderType);
        return *this;
    }

    MeshInstance &MeshInstance::operator=(const MeshInstance &other) {
        vertices = other.vertices;
        indices = other.indices;
        rotMatrix = other.rotMatrix;
        transMatrix = other.transMatrix;
        scaleMatrix = other.scaleMatrix;
        modelMatrix = other.modelMatrix;
        if (other.VAO_initialised) {
            this->initialiseVAO();
        }
        return *this;
    }

    MeshInstance::~MeshInstance() {
        clearVAO();
    }

    void MeshInstance::initialiseVAO() {

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &vertexBuffer);
        glGenBuffers(1, &indexBuffer);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices.front(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid * ) 0); // Position Vector

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (sizeof(float) * 3)); // Normal Vector

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (sizeof(float) * 6)); // RGBA Values

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (sizeof(float) * 10)); // UV Coords

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);

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
        VAO_initialised = true;
    }

    void MeshInstance::clearVAO() {
        if (VAO_initialised) {
			glDeleteBuffers(1, &vertexBuffer);
			glDeleteBuffers(1, &indexBuffer);
            glDeleteBuffers(1, &transformBuffer);
			glDeleteVertexArrays(1, &VAO);
        }
    }

    void MeshInstance::render(const Shader &program, const Camera &renderCamera, bool update_gpu_data) {
        if (!VAO_initialised) initialiseVAO();
        program.bind();
        glm::mat4x4 temp1, temp2;
        if (program.getUniformLoc("proj") != -1) {
            temp1 = renderCamera.getPMatrix();
            glUniformMatrix4fv(program.getUniformLoc("proj"), 1, GL_FALSE, (const GLfloat *) &temp1);
        };
        if (program.getUniformLoc("view") != -1) {
            temp2 = renderCamera.getVMatrix();
            glUniformMatrix4fv(program.getUniformLoc("view"), 1, GL_FALSE, (const GLfloat *) &temp2);
        };

        glBindVertexArray(VAO);

        if (update_gpu_data) {
            glNamedBufferSubData(transformBuffer, 0, modelMatrix.size() * sizeof(glm::mat4x4),
                                 (GLvoid * ) & modelMatrix.front());
        }

        glDrawElementsInstanced(renderType, (GLsizei) indices.size(), GL_UNSIGNED_INT, 0,
                                (GLsizei) modelMatrix.size());
		check_gl_error();

        glBindVertexArray(0);
        cogl::Shader::unbind();
    }

    void MeshInstance::rotateMesh(const int objectID, const double &angle, const glm::vec3 &axisOfRotation) {
        if (objectID == -1) {
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
    }

    void
    MeshInstance::addInstance(const glm::mat4x4 &transform, const glm::mat4x4 &rotation, const glm::mat4x4 &scale) {
        transMatrix.push_back(transform);
        rotMatrix.push_back(rotation);
        scaleMatrix.push_back(scale);
        modelMatrix.push_back(transform * rotation * scale);
    }

    void
    MeshInstance::addInstances(const std::vector<glm::mat4x4> &transforms, const std::vector<glm::mat4x4> &rotations,
                               const std::vector<glm::mat4x4> &scales) {
        for (auto i = 0; i < transforms.size(); ++i) addInstance(transforms[i], rotations[i], scales[i]);

    }

    void MeshInstance::addInstance(const glm::mat4x4 &modelMatrix) {
        transMatrix.emplace_back(1.0f);
        rotMatrix.push_back(glm::extractMatrixRotation(modelMatrix));
        transMatrix.back()[3] = modelMatrix[3] / modelMatrix[3][3];
        scaleMatrix.push_back(glm::inverse(rotMatrix.back()) * glm::inverse(transMatrix.back()) * modelMatrix);
        this->modelMatrix.push_back(transMatrix.back() * rotMatrix.back() * scaleMatrix.back());
    }

    void MeshInstance::addInstances(const std::vector<glm::mat4x4> &modelMatrices) {
        for (auto i : modelMatrices) addInstance(i);
    }

    void MeshInstance::removeInstanceHelper(const unsigned long long objectID) {
        if (objectID < transMatrix.size()) {
            transMatrix.erase(transMatrix.begin() + objectID);
            rotMatrix.erase(rotMatrix.begin() + objectID);
            scaleMatrix.erase(scaleMatrix.begin() + objectID);
            std::remove(indices.begin(), indices.end(), objectID);
        }
    }

    void MeshInstance::removeInstance(const unsigned long long objectID) {
        if (objectID < transMatrix.size()) {
            removeInstanceHelper(objectID);
            clearVAO();
            initialiseVAO();
        }
    }

    void MeshInstance::removeInstances(const std::vector<unsigned long long> objectID) {
        for (auto &&i : objectID) {
            if (i < transMatrix.size()) removeInstanceHelper(i);
        }
        clearVAO();
        initialiseVAO();
    }

}

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
        normalMatrix = std::vector<glm::mat4x4>();
        normalMatrix.reserve(25);
        modelMatrix = std::vector<glm::mat4x4>();
        modelMatrix.reserve(25);
        changedMatrices = std::vector<bool>(25);
    }

    MeshInstance::MeshInstance(const MeshInstance &other) {
        vertices = other.vertices;
        indices = other.indices;
        rotMatrix = other.rotMatrix;
        transMatrix = other.transMatrix;
        scaleMatrix = other.scaleMatrix;
        normalMatrix = other.normalMatrix;
        modelMatrix = other.modelMatrix;
        changedMatrices = other.changedMatrices;
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
        normalMatrix = std::vector<glm::mat4x4>();
        normalMatrix.reserve(25);
        modelMatrix = std::vector<glm::mat4x4>();
        modelMatrix.reserve(25);
        changedMatrices = std::vector<bool>(25);
        rotMatrix.emplace_back(1.0f);
        transMatrix.emplace_back(1.0f);
        scaleMatrix.emplace_back(1.0f);
        normalMatrix.emplace_back(1.0f);
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
        normalMatrix = std::vector<glm::mat4x4>();
        normalMatrix.reserve(25);
        modelMatrix = std::vector<glm::mat4x4>();
        modelMatrix.reserve(25);
        changedMatrices = std::vector<bool>(25);
        rotMatrix.emplace_back(1.0f);
        transMatrix.emplace_back(1.0f);
        scaleMatrix.emplace_back(1.0f);
        normalMatrix.emplace_back(1.0f);
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
        normalMatrix = std::vector<glm::mat4x4>();
        normalMatrix.reserve(transformMatrices.size());
        modelMatrix = std::vector<glm::mat4x4>();
        modelMatrix.reserve(transformMatrices.size());
        modelMatrix = std::vector<glm::mat4x4>(transformMatrices);
        changedMatrices = std::vector<bool>(transformMatrices.size());
        for (auto &i : transformMatrices) {
            transMatrix.emplace_back(1.0f);
            rotMatrix.push_back(glm::extractMatrixRotation(i));
            normalMatrix.push_back(glm::inverseTranspose(i));
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
        normalMatrix = std::vector<glm::mat4x4>(numCopies, other.getNormalMatrix());
        modelMatrix = std::vector<glm::mat4x4>(numCopies, other.getModelMatrix());
        changedMatrices = std::vector<bool>(numCopies);
        renderType = other.getRenderType();
    }

    MeshInstance::MeshInstance(MeshInstance &&other) {
        std::swap(this->VAO, other.VAO);
        std::swap(this->transformBuffer, other.transformBuffer);
        std::swap(this->normalBuffer, other.normalBuffer);
        std::swap(this->VAO_initialised, other.VAO_initialised);
        std::swap(this->vertices, other.vertices);
        std::swap(this->indices, other.indices);
        std::swap(this->rotMatrix, other.rotMatrix);
        std::swap(this->transMatrix, other.transMatrix);
        std::swap(this->scaleMatrix, other.scaleMatrix);
        std::swap(this->normalMatrix, other.normalMatrix);
        std::swap(this->changedMatrices, other.changedMatrices);
        std::swap(this->renderType, other.renderType);
    }

    MeshInstance &MeshInstance::operator=(MeshInstance &&other) {
        std::swap(this->VAO, other.VAO);
        std::swap(this->transformBuffer, other.transformBuffer);
        std::swap(this->normalBuffer, other.normalBuffer);
        std::swap(this->VAO_initialised, other.VAO_initialised);
        std::swap(this->vertices, other.vertices);
        std::swap(this->indices, other.indices);
        std::swap(this->rotMatrix, other.rotMatrix);
        std::swap(this->transMatrix, other.transMatrix);
        std::swap(this->scaleMatrix, other.scaleMatrix);
        std::swap(this->normalMatrix, other.normalMatrix);
        std::swap(this->changedMatrices, other.changedMatrices);
        std::swap(this->renderType, other.renderType);
        return *this;
    }

    MeshInstance &MeshInstance::operator=(const MeshInstance &other) {
        vertices = other.vertices;
        indices = other.indices;
        rotMatrix = other.rotMatrix;
        transMatrix = other.transMatrix;
        scaleMatrix = other.scaleMatrix;
        normalMatrix = other.normalMatrix;
        modelMatrix = other.modelMatrix;
        changedMatrices = other.changedMatrices;
        return *this;
    }

    MeshInstance::~MeshInstance() {
        clearVAO();
    }

    void MeshInstance::initialiseVAO() {
        GLuint vertexBuffer, indexBuffer;

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &vertexBuffer);
        glGenBuffers(1, &indexBuffer);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) 0); // Position Vector

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (GLvoid *) (sizeof(float) * 3)); // Normal Vector

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (sizeof(float) * 6)); // RGBA Values

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (sizeof(float) * 10)); // UV Coords

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

        glGenBuffers(1, &transformBuffer);
        glGenBuffers(1, &normalBuffer);

        glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
        glBufferData(GL_ARRAY_BUFFER, modelMatrix.size() * sizeof(glm::mat4x4), (GLvoid *) &(modelMatrix.front()),
                     GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (GLvoid *) 0);
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (GLvoid *) (sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (GLvoid *) (sizeof(glm::vec4) * 2));
        glEnableVertexAttribArray(7);
        glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (GLvoid *) (sizeof(glm::vec4) * 3));
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glBufferData(GL_ARRAY_BUFFER, normalMatrix.size() * sizeof(glm::mat4x4), (GLvoid *) &(normalMatrix.front()),
                     GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glEnableVertexAttribArray(8);
        glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (GLvoid *) 0);
        glEnableVertexAttribArray(9);
        glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (GLvoid *) (sizeof(glm::vec4)));
        glEnableVertexAttribArray(10);
        glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (GLvoid *) (sizeof(glm::vec4) * 2));
        glEnableVertexAttribArray(11);
        glVertexAttribPointer(11, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (GLvoid *) (sizeof(glm::vec4) * 3));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribDivisor(0, 0);
        glVertexAttribDivisor(1, 0);
        glVertexAttribDivisor(2, 0);
        glVertexAttribDivisor(3, 0);
        for (GLuint i = 4; i <= 11; ++i) glVertexAttribDivisor(i, 1);

        glBindVertexArray(0);
        glDeleteBuffers(1, &vertexBuffer);
        glDeleteBuffers(1, &indexBuffer);
        VAO_initialised = true;
    }

    void MeshInstance::clearVAO() {
        if (VAO_initialised) {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &transformBuffer);
            glDeleteBuffers(1, &normalBuffer);
        }
    }

    void MeshInstance::render(const Shader &program, const Camera &renderCamera) {
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
        glDrawElementsInstanced(renderType, (GLsizei) indices.size(), GL_UNSIGNED_INT, (GLvoid *) 0,
                                (GLsizei) modelMatrix.size());
        glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
        if (renderType != RenderTypes::Points) {
            if (modelMatrix.size() > MeshInstance::SUBDIVIDE_UPDATE_MESH_COUNT) {
                for (auto i = 0; i < modelMatrix.size(); i++) {
                    if (changedMatrices[i]) {
                        glBufferSubData(GL_ARRAY_BUFFER, i * sizeof(glm::mat4x4), sizeof(glm::mat4x4),
                                        (GLvoid *) &modelMatrix[i]);
                        changedMatrices[i] = false;
                    }
                }
            } else {
                glBufferSubData(GL_ARRAY_BUFFER, 0, modelMatrix.size() * sizeof(glm::mat4x4),
                                (GLvoid *) &modelMatrix.front());
            }
            glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
            if (normalMatrix.size() > MeshInstance::SUBDIVIDE_UPDATE_MESH_COUNT) {
                for (auto i = 0; i < normalMatrix.size(); i++) {
                    if (changedMatrices[i]) {
                        glBufferSubData(GL_ARRAY_BUFFER, i * sizeof(glm::mat4x4), sizeof(glm::mat4x4),
                                        (GLvoid *) &normalMatrix[i]);
                        changedMatrices[i] = false;
                    }
                }
            } else {
                glBufferSubData(GL_ARRAY_BUFFER, 0, normalMatrix.size() * sizeof(glm::mat4x4),
                                (GLvoid *) &normalMatrix.front());
            }
        } else {
            if (modelMatrix.size() > MeshInstance::SUBDIVIDE_UPDATE_MESH_COUNT) {
                for (auto i = 0; i < modelMatrix.size(); i++) {
                    if (changedMatrices[i]) {
                        glBufferSubData(GL_ARRAY_BUFFER, i * sizeof(glm::mat4x4) + 3 * sizeof(glm::vec4),
                                        sizeof(glm::vec4), (GLvoid *) &modelMatrix[i][3]);
                        changedMatrices[i] = false;
                    }
                }
            } else {
                glBufferSubData(GL_ARRAY_BUFFER, 0, modelMatrix.size() * sizeof(glm::mat4x4),
                                (GLvoid *) &modelMatrix.front());
            }
        }
        glBindVertexArray(0);
        program.unbind();
    }

    void MeshInstance::rotateMesh(const int objectID, const double &angle, const glm::vec3 &axisOfRotation) {
        if (objectID == -1) {
            for (auto i = 0; i < rotMatrix.size(); ++i) {
                rotMatrix[i] = glm::rotate((float) angle, axisOfRotation) * rotMatrix[i];
                if (renderType != RenderTypes::Points) {
                    modelMatrix[i] = transMatrix[i] * rotMatrix[i] * scaleMatrix[i];
                    normalMatrix[i] = glm::inverseTranspose(getModelMatrix(i));
                } else {
                    modelMatrix[i] = transMatrix[i];
                }
            }
            changedMatrices = std::vector<bool>(changedMatrices.size(), true);
        } else {
            rotMatrix[objectID] = glm::rotate((float) angle, axisOfRotation) * rotMatrix[objectID];
            modelMatrix[objectID] = transMatrix[objectID] * rotMatrix[objectID] * scaleMatrix[objectID];
            normalMatrix[objectID] = glm::inverseTranspose(getModelMatrix(objectID));
            changedMatrices[objectID] = true;
        }
    }

    void MeshInstance::scaleMesh(const int objectID, const double &xScale, const double &yScale, const double &zScale) {
        if (objectID == -1) {
            for (auto i = 0; i < rotMatrix.size(); ++i) {
                scaleMatrix[i] = glm::scale(glm::vec3({xScale, yScale, zScale})) * scaleMatrix[i];
                if (renderType != RenderTypes::Points) {
                    modelMatrix[i] = transMatrix[i] * rotMatrix[i] * scaleMatrix[i];
                    normalMatrix[i] = glm::inverseTranspose(getModelMatrix(i));
                } else {
                    modelMatrix[i] = transMatrix[i];
                }
            }
            changedMatrices = std::vector<bool>(changedMatrices.size(), true);
        } else {
            scaleMatrix[objectID] = glm::scale(glm::vec3({xScale, yScale, zScale})) * scaleMatrix[objectID];
            modelMatrix[objectID] = transMatrix[objectID] * rotMatrix[objectID] * scaleMatrix[objectID];
            normalMatrix[objectID] = glm::inverseTranspose(getModelMatrix(objectID));
            changedMatrices[objectID] = true;
        }
    }

    void MeshInstance::moveMesh(const int objectID, const glm::vec3 &translation) {
        if (objectID == -1) {
            for (auto i = 0; i < rotMatrix.size(); ++i) {
                transMatrix[i] = glm::translate(translation) * transMatrix[i];
                if (renderType != RenderTypes::Points) {
                    modelMatrix[i] = transMatrix[i] * rotMatrix[i] * scaleMatrix[i];
                    normalMatrix[i] = glm::inverseTranspose(getModelMatrix(i));
                } else {
                    modelMatrix[i] = transMatrix[i];
                }
            }
            changedMatrices = std::vector<bool>(changedMatrices.size(), true);
        } else {
            transMatrix[objectID] = glm::translate(translation) * transMatrix[objectID];
            modelMatrix[objectID] = transMatrix[objectID] * rotMatrix[objectID] * scaleMatrix[objectID];
            normalMatrix[objectID] = glm::inverseTranspose(getModelMatrix(objectID));
            changedMatrices[objectID] = true;
        }
    }

    void MeshInstance::moveMeshTo(const int objectID, const glm::vec3 &translation) {
        if (objectID == -1) {
            for (auto i = 0; i < transMatrix.size(); ++i) {
                transMatrix[i] = glm::translate(glm::mat4x4(1.0f), translation);
                if (renderType != RenderTypes::Points) {
                    modelMatrix[i] = transMatrix[i] * rotMatrix[i] * scaleMatrix[i];
                    normalMatrix[i] = glm::inverseTranspose(getModelMatrix(i));
                } else {
                    modelMatrix[i] = transMatrix[i];
                }
            }
            changedMatrices = std::vector<bool>(changedMatrices.size(), true);
        } else {
            transMatrix[objectID] = glm::translate(glm::mat4x4(1.0f), translation);
            modelMatrix[objectID] = transMatrix[objectID] * rotMatrix[objectID] * scaleMatrix[objectID];
            normalMatrix[objectID] = glm::inverseTranspose(getModelMatrix(objectID));
            changedMatrices[objectID] = true;
        }
    }

    void MeshInstance::moveMeshTo(const std::vector<glm::vec3> &translation) {
        for (auto i = 0; i < translation.size(); ++i) {
            transMatrix[i] = glm::translate(glm::mat4x4(1.0f), translation[i]);
            if (renderType != RenderTypes::Points) {
                modelMatrix[i] = transMatrix[i] * rotMatrix[i] * scaleMatrix[i];
                normalMatrix[i] = glm::inverseTranspose(getModelMatrix(i));
            } else {
                modelMatrix[i] = transMatrix[i];
            }
        }
        changedMatrices = std::vector<bool>(changedMatrices.size(), true);
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

    const glm::mat4x4 &MeshInstance::getNormalMatrix(const int objectID) const {
        return normalMatrix[objectID];
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

    const std::vector<glm::mat4x4> &MeshInstance::getNormalMatrix() const {
        return normalMatrix;
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
        normalMatrix.push_back(glm::inverseTranspose(modelMatrix.back()));
        changedMatrices.push_back(false);
    }

    void
    MeshInstance::addInstance(const glm::mat4x4 &transform, const glm::mat4x4 &rotation, const glm::mat4x4 &scale) {
        transMatrix.push_back(transform);
        rotMatrix.push_back(rotation);
        scaleMatrix.push_back(scale);
        modelMatrix.push_back(transform * rotation * scale);
        normalMatrix.push_back(glm::inverseTranspose(modelMatrix.back()));
        changedMatrices.push_back(false);
    }

    void
    MeshInstance::addInstances(const std::vector<glm::mat4x4> &transforms, const std::vector<glm::mat4x4> &rotations,
                               const std::vector<glm::mat4x4> &scales) {
        for (auto i = 0; i < transforms.size(); ++i) addInstance(transforms[i], rotations[i], scales[i]);

    }

    void MeshInstance::addInstance(const glm::mat4x4 &modelMatrix) {
        transMatrix.push_back(glm::mat4x4(1.0f));
        rotMatrix.push_back(glm::extractMatrixRotation(modelMatrix));
        normalMatrix.push_back(glm::inverseTranspose(modelMatrix));
        transMatrix.back()[3] = modelMatrix[3] / modelMatrix[3][3];
        scaleMatrix.push_back(glm::inverse(rotMatrix.back()) * glm::inverse(transMatrix.back()) * modelMatrix);
        this->modelMatrix.push_back(transMatrix.back() * rotMatrix.back() * scaleMatrix.back());
        changedMatrices.push_back(false);
    }

    void MeshInstance::addInstances(const std::vector<glm::mat4x4> &modelMatrices) {
        for (auto i : modelMatrices) addInstance(i);
    }

    void MeshInstance::removeInstanceHelper(const unsigned long long objectID) {
        if (objectID < transMatrix.size()) {
            transMatrix.erase(transMatrix.begin() + objectID);
            rotMatrix.erase(rotMatrix.begin() + objectID);
            normalMatrix.erase(normalMatrix.begin() + objectID);
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

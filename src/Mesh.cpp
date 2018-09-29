//
// Created by ekin4 on 23/02/2017.
//

#include "cogl/Mesh.h"

namespace cogl {
    Mesh::Mesh(const std::vector<Vertex> &verticesInit) : meshRepr(verticesInit){
        rotMatrix = glm::mat4x4(1.0f);
        transMatrix = glm::mat4x4(1.0f);
        scaleMatrix = glm::mat4x4(1.0f);
        normalMatrix = glm::mat4x4(1.0f);
        renderType = RenderTypes::Tris;

        initialiseVAO();
    }

    Mesh::Mesh(const std::vector<Vertex> &verticesInit, const std::vector<unsigned int> &indicesInit,
               RenderTypes rType) : meshRepr(verticesInit, indicesInit) {
        rotMatrix = glm::mat4x4(1.0f);
        transMatrix = glm::mat4x4(1.0f);
        scaleMatrix = glm::mat4x4(1.0f);
        normalMatrix = glm::mat4x4(1.0f);
        renderType = rType;

        initialiseVAO();
    }

    Mesh::Mesh(MeshRepresentation other) : meshRepr(std::move(other)) {
        rotMatrix = glm::mat4x4(1.0f);
        transMatrix = glm::mat4x4(1.0f);
        scaleMatrix = glm::mat4x4(1.0f);
        normalMatrix = glm::mat4x4(1.0f);
        renderType = RenderTypes::Tris;

        initialiseVAO();
    }

    Mesh::Mesh(Mesh &&other) noexcept : meshRepr(std::move(other.meshRepr)), VAO(other.VAO), vertexBuffer(other.vertexBuffer), indexBuffer(other.indexBuffer){
        other.VAO = 0;
        other.vertexBuffer = 0;
        other.indexBuffer = 0;
        std::swap(this->rotMatrix, other.rotMatrix);
        std::swap(this->transMatrix, other.transMatrix);
        std::swap(this->scaleMatrix, other.scaleMatrix);
        std::swap(this->normalMatrix, other.normalMatrix);
        std::swap(this->renderType, other.renderType);
    }

    Mesh &Mesh::operator=(Mesh &&other) noexcept {
        if (this != &other) {
            release();
            this->meshRepr = MeshRepresentation(other.meshRepr);
            std::swap(this->VAO, other.VAO);
            std::swap(this->vertexBuffer, other.vertexBuffer);
            std::swap(this->indexBuffer, other.indexBuffer);
            std::swap(this->rotMatrix, other.rotMatrix);
            std::swap(this->transMatrix, other.transMatrix);
            std::swap(this->scaleMatrix, other.scaleMatrix);
            std::swap(this->normalMatrix, other.normalMatrix);
            std::swap(this->renderType, other.renderType);
        }
        return *this;
    }

    Mesh::~Mesh() {
        release();
    }

    void Mesh::initialiseVAO() {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &vertexBuffer);
        glGenBuffers(1, &indexBuffer);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, meshRepr.vertices.size() * sizeof(Vertex), meshRepr.vertices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr); // Position Vector

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (sizeof(float) * 3)); // Normal Vector

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (sizeof(float) * 6)); // RGBA Values

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (sizeof(float) * 10)); // UV Coords

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshRepr.indices.size() * sizeof(unsigned int), meshRepr.indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    void Mesh::release() {
        glDeleteBuffers(1, &vertexBuffer);
        glDeleteBuffers(1, &indexBuffer);
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
        vertexBuffer = 0;
        indexBuffer = 0;
    }

    void Mesh::render(const Shader &program, const Camera &renderCamera, bool update_gpu_data) {
        program.bind();
        glm::mat4x4 temp;
        if (program.getUniformLoc("mvp") != -1) {
            temp = renderCamera.getMVPMatrix(getModelMatrix());
            glUniformMatrix4fv(program.getUniformLoc("mvp"), 1, GL_FALSE, (const GLfloat *) &temp[0][0]);
        };
        if (program.getUniformLoc("proj") != -1) {
            temp = renderCamera.getPMatrix();
            glUniformMatrix4fv(program.getUniformLoc("proj"), 1, GL_FALSE, (const GLfloat *) &temp[0][0]);
        };
        if (program.getUniformLoc("view") != -1) {
            temp = renderCamera.getVMatrix();
            glUniformMatrix4fv(program.getUniformLoc("view"), 1, GL_FALSE, (const GLfloat *) &temp[0][0]);
        };
        if (program.getAttribLoc("modelMatrix") != -1 && update_gpu_data) {
            temp = getModelMatrix();
            glVertexAttrib4fv(static_cast<GLuint>(program.getAttribLoc("modelMatrix")), (const GLfloat *) &temp[0][0]);
        };
        if (program.getAttribLoc("normalMatrix") != -1 && update_gpu_data) {
            temp = getNormalMatrix();
            glVertexAttrib4fv(static_cast<GLuint>(program.getAttribLoc("normalMatrix")), (const GLfloat *) &temp[0][0]);
        };
        if (program.getAttribLoc("uTessLevel") != -1) {
            float tessLevel = 2.0;
            glVertexAttrib4fv(static_cast<GLuint>(program.getAttribLoc("uTessLevel")), (const GLfloat *) &tessLevel);
        };
        glBindVertexArray(VAO);
        glDrawElements(renderType, static_cast<GLsizei>(meshRepr.indices.size()), GL_UNSIGNED_INT, (void *) 0);
        glBindVertexArray(0);
        cogl::Shader::unbind();
    }

    void Mesh::rotateMesh(const double angle, const glm::vec3 axisOfRotation) {
        rotMatrix = glm::rotate((float) angle, axisOfRotation) * rotMatrix;
        normalMatrix = glm::inverseTranspose(getModelMatrix());
    }

    void Mesh::scaleMesh(const double xScale, const double yScale, const double zScale) {
        scaleMatrix = glm::scale(glm::vec3({xScale, yScale, zScale})) * scaleMatrix;
        normalMatrix = glm::inverseTranspose(getModelMatrix());
    }

    void Mesh::moveMesh(const glm::vec3 translation) {
        transMatrix = glm::translate(translation) * transMatrix;
        normalMatrix = glm::inverseTranspose(getModelMatrix());
    }

    void Mesh::moveMeshTo(const glm::vec3 translation) {
        transMatrix = glm::translate(translation);
        check_gl_error();
        normalMatrix = glm::inverseTranspose(getModelMatrix());
        check_gl_error();
    }

    void Mesh::setRenderType(const RenderTypes rType) {
        renderType = rType;
    }

    const MeshRepresentation Mesh::getMeshRepresentation() const {
        return MeshRepresentation(this->meshRepr);
    }

    const glm::mat4x4 Mesh::getModelMatrix() const {
        return (transMatrix * rotMatrix * scaleMatrix);
    }

    const glm::mat4x4 Mesh::getNormalMatrix() const {
        return (normalMatrix);
    }

    RenderTypes Mesh::getRenderType() const {
        return renderType;
    }

    const glm::mat4x4 Mesh::getTransMatrix() const {
        return transMatrix;
    }

    const glm::mat4x4 Mesh::getRotMatrix() const {
        return rotMatrix;
    }

    const glm::mat4x4 Mesh::getScaleMatrix() const {
        return scaleMatrix;
    }

    Mesh Mesh::load_from_obj(const std::string filename) {
        return Mesh(MeshRepresentation::load_from_obj(filename));
    }

    MeshRepresentation::operator Mesh() const {
        return Mesh(*this);
    }
};
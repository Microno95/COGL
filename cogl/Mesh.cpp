//
// Created by ekin4 on 23/02/2017.
//

#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

namespace cogl {

    Mesh::Mesh() {
        vertices = std::vector<Vertex>();
        indices = std::vector<unsigned int>();
        rotMatrix = glm::mat4x4(1.0f);
        transMatrix = glm::mat4x4(1.0f);
        scaleMatrix = glm::mat4x4(1.0f);
        normalMatrix = glm::mat4x4(1.0f);
        renderType = RenderTypes::Tris;
    }

    Mesh::Mesh(const Mesh &other) {
        this->vertices = other.vertices;
        this->indices = other.indices;
        rotMatrix = glm::mat4x4(1.0f);
        transMatrix = glm::mat4x4(1.0f);
        scaleMatrix = glm::mat4x4(1.0f);
        normalMatrix = glm::mat4x4(1.0f);
        renderType = RenderTypes::Tris;
    }

    Mesh::Mesh(const std::vector<Vertex> &verticesInit) {
        this->vertices = std::vector<Vertex>(verticesInit);
        this->indices = std::vector<unsigned int>();
        for (unsigned int i = 0; i < vertices.size(); i++) indices.push_back(i);
        rotMatrix = glm::mat4x4(1.0f);
        transMatrix = glm::mat4x4(1.0f);
        scaleMatrix = glm::mat4x4(1.0f);
        normalMatrix = glm::mat4x4(1.0f);
        renderType = RenderTypes::Tris;
    }

    Mesh::Mesh(const std::vector<Vertex> &verticesInit, const std::vector<unsigned int> &indicesInit,
               RenderTypes rType) {
        this->vertices = std::vector<Vertex>(verticesInit);
        this->indices = std::vector<unsigned int>(indicesInit);
        this->renderType = rType;
        rotMatrix = glm::mat4x4(1.0f);
        transMatrix = glm::mat4x4(1.0f);
        scaleMatrix = glm::mat4x4(1.0f);
        normalMatrix = glm::mat4x4(1.0f);
    }

    Mesh::Mesh(Mesh &&other) {
        std::swap(this->VAO, other.VAO);
        std::swap(this->vertexBuffer, other.vertexBuffer);
        std::swap(this->indexBuffer, other.indexBuffer);
        std::swap(this->vertices, other.vertices);
        std::swap(this->indices, other.indices);
        std::swap(this->rotMatrix, other.rotMatrix);
        std::swap(this->transMatrix, other.transMatrix);
        std::swap(this->scaleMatrix, other.scaleMatrix);
        std::swap(this->normalMatrix, other.normalMatrix);
        std::swap(this->renderType, other.renderType);
    }

    Mesh &Mesh::operator=(Mesh &&other) {
        std::swap(this->VAO, other.VAO);
        std::swap(this->vertexBuffer, other.vertexBuffer);
        std::swap(this->indexBuffer, other.indexBuffer);
        std::swap(this->vertices, other.vertices);
        std::swap(this->indices, other.indices);
        std::swap(this->rotMatrix, other.rotMatrix);
        std::swap(this->transMatrix, other.transMatrix);
        std::swap(this->scaleMatrix, other.scaleMatrix);
        std::swap(this->normalMatrix, other.normalMatrix);
        std::swap(this->renderType, other.renderType);
        return *this;
    }

    Mesh &Mesh::operator=(const Mesh &other) {
        this->vertices = other.vertices;
        this->indices = other.indices;
        rotMatrix = glm::mat4x4(1.0f);
        transMatrix = glm::mat4x4(1.0f);
        scaleMatrix = glm::mat4x4(1.0f);
        normalMatrix = glm::mat4x4(1.0f);
        renderType = RenderTypes::Tris;
        return *this;
    }

    Mesh::~Mesh() {
        clearVAO();
    }

    void Mesh::initialiseVAO() {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &vertexBuffer);
        glGenBuffers(1, &indexBuffer);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr); // Position Vector

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (sizeof(float) * 3)); // Normal Vector

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (sizeof(float) * 6)); // RGBA Values

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (sizeof(float) * 10)); // UV Coords

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
        VAO_initialised = true;
    }

    void Mesh::clearVAO() {
        glDeleteBuffers(1, &vertexBuffer);
        glDeleteBuffers(1, &indexBuffer);
        glDeleteVertexArrays(1, &VAO);
    }

    void Mesh::render(const Shader &program, const Camera &renderCamera, bool update_gpu_data) {
        if (!VAO_initialised) initialiseVAO();
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
            glVertexAttrib4fv(program.getAttribLoc("modelMatrix"), (const GLfloat *) &temp[0][0]);
        };
        if (program.getAttribLoc("normalMatrix") != -1 && update_gpu_data) {
            temp = getNormalMatrix();
            glVertexAttrib4fv(program.getAttribLoc("normalMatrix"), (const GLfloat *) &temp[0][0]);
        };
        if (program.getAttribLoc("uTessLevel") != -1) {
            float tessLevel = 2.0;
            glVertexAttrib4fv(program.getAttribLoc("uTessLevel"), (const GLfloat *) &tessLevel);
        };
        glBindVertexArray(VAO);
        glDrawElements(renderType, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
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

    const std::vector<Vertex> Mesh::getVertices() const {
        return std::vector<Vertex>(this->vertices);
    }

    const std::vector<unsigned int> Mesh::getIndices() const {
        return std::vector<unsigned int>(this->indices);
    }

    const glm::mat4x4 Mesh::getModelMatrix() const {
        return (transMatrix * rotMatrix * scaleMatrix);
    }

    const glm::mat4x4 Mesh::getNormalMatrix() const {
        return (normalMatrix);
    }

    const RenderTypes Mesh::getRenderType() const {
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

    const Mesh Mesh::Cube = Mesh(std::vector<Vertex>(
            {{-1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
             {1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
             {1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
             {-1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
             {-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
             {1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
             {1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
             {-1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f}}),
                                 std::vector<unsigned int>({/*front*/ 0, 1, 2, 2, 3, 0,   /*top*/  1, 5, 6, 6, 2, 1,
                                                                   /*back*/  7, 6, 5, 5, 4, 7, /*bottom*/ 4, 0, 3, 3, 7,
                                                                      4,
                                                                   /*left*/  4, 5, 1, 1, 0, 4,  /*right*/ 3, 2, 6, 6, 7,
                                                                      3,}));

    const Mesh Mesh::Icosahedron = Mesh(std::vector<Vertex>(
            {{0.000f,  0.000f,  1.000f,  -1.0f, -1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
             {0.894f,  0.000f,  0.447f,  1.0f,  -1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
             {0.276f,  0.851f,  0.447f,  1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
             {-0.724f, 0.526f,  0.447f,  -1.0f, 1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
             {-0.724f, -0.526f, 0.447f,  -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
             {0.276f,  -0.851f, 0.447f,  1.0f,  -1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
             {0.724f,  0.526f,  -0.447f, 1.0f,  1.0f,  -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
             {-0.276f, 0.851f,  -0.447f, 1.0f,  1.0f,  -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
             {-0.894f, 0.000f,  -0.447f, 1.0f,  1.0f,  -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
             {-0.276f, -0.851f, -0.447f, 1.0f,  1.0f,  -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
             {0.724f,  -0.526f, -0.447f, 1.0f,  1.0f,  -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
             {0.000f,  0.000f,  -1.000f, -1.0f, 1.0f,  -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f}}),
                                        std::vector<unsigned int>({2, 1, 0, 3, 2, 0, 4, 3, 0, 5, 4, 0,
                                                                   1, 5, 0, 11, 6, 7, 11, 7, 8, 11, 8, 9,
                                                                   11, 9, 10, 11, 10, 6, 1, 2, 6, 2, 3, 7,
                                                                   3, 4, 8, 4, 5, 9, 5, 1, 10, 2, 7, 6,
                                                                   3, 8, 7, 4, 9, 8, 5, 10, 9, 1, 6, 10}));

    Mesh Mesh::load_from_obj(const std::string filename) {
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

        return Mesh(verticesVector, indicesVector);
    }
}
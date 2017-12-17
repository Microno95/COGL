//
// Created by ekin4 on 28/04/2017.
//

#include "../../Constants.h"
#include "../../cogl.h"

int main() {
    cogl::GLWindow mainWindow(1, 4, 0);
    mainWindow.enableCapability(GL_VERTEX_PROGRAM_POINT_SIZE);
//    mainWindow.enableCapability(GL_DEPTH_TEST);
//    mainWindow.enableCapability(GL_CULL_FACE);
//    mainWindow.setCullType(GL_BACK);
//    mainWindow.setDepthFunction(GL_LESS);
    mainWindow.setAASamples(1);

    using Vertex = cogl::Vertex;
    using m4 = glm::mat4x4;

    auto vertices = std::vector<Vertex>({{0.0f, 0.0f, 0.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f}});
    auto indices = std::vector<unsigned int>({0});

    std::vector<glm::vec3> offsets;
    offsets.resize(50000);

    float radius = 4;
    float angle = 0.0;

    for (auto i = 0; i < offsets.size(); ++i) {
        glm::vec3 dest = {glm::cos(angle), 0.0f, glm::sin(angle)};
        dest *= radius;
        offsets[i] = dest;
        angle += (float) (2 * PI / offsets.size());
    }

    GLuint vertexBuffer, indexBuffer, VAO, transformBuffer;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &indexBuffer);
    glGenBuffers(1, &transformBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices.front(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) nullptr); // Position Vector

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid *) (sizeof(float) * 3)); // Normal Vector

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (sizeof(float) * 6)); // RGBA Values

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (sizeof(float) * 10)); // UV Coords

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
    glBufferData(GL_ARRAY_BUFFER, offsets.size() * sizeof(glm::vec3), (GLvoid *) &(offsets.front()),
                 GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid *) nullptr);

    glVertexAttribDivisor(4, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);


    cogl::Camera defaultCamera = cogl::Camera(glm::vec3(5.0f, 5.0f, -5.0f),
                                              glm::vec3({0.f, 0.f, 0.f}),
                                              glm::vec3({0.0f, 1.0f, 0.0f}), cogl::projection::perspective);
    defaultCamera.changeAR(16.0 / 9.0);

    defaultCamera.setEventHandling();

    cogl::Shader defShader("cogl/shaders/pointsTest");

    std::cout << defShader.Program << " | " << (glIsProgram(defShader.Program) == GL_TRUE) << std::endl;

    double previousTime = glfwGetTime();
    int frameCount = 0;
    int frameCounterDebug = 0;

    while (!mainWindow.shouldClose()) {
        mainWindow.renderBegin();
        defShader.bind();

        glm::mat4x4 temp1, temp2;

        if (defShader.getUniformLoc("proj") != -1) {
            temp1 = defaultCamera.getPMatrix();
            glUniformMatrix4fv(defShader.getUniformLoc("proj"), 1, GL_FALSE, (const GLfloat *) &temp1);
            check_gl_error();
        };
        if (defShader.getUniformLoc("view") != -1) {
            temp2 = defaultCamera.getVMatrix();
            glUniformMatrix4fv(defShader.getUniformLoc("view"), 1, GL_FALSE, (const GLfloat *) &temp2);
            check_gl_error();
        };
//        if (defShader.getUniformLoc("model") != -1) {
//            glUniform3fv(defShader.getUniformLoc("model"), 100, (const GLfloat *) &offsets.front());
//            check_gl_error();
//        }

        glBindVertexArray(VAO);
        glNamedBufferSubData(transformBuffer, 0, offsets.size(), (GLvoid *) &offsets.front());
        check_gl_error();
        printf("Initiating instanced draw calls\n");
        glDrawElementsInstanced(cogl::RenderTypes::Points, (GLsizei) indices.size(), GL_UNSIGNED_INT, nullptr,
                                (GLsizei) offsets.size());
        check_gl_error();

        glBindVertexArray(0);
        glFinish();

        defShader.unbind();
        mainWindow.renderEnd();
        double currentTime = glfwGetTime();
        frameCount++;
        if (currentTime - previousTime >= 1.0) {
            // Display the frame count here any way you want.
            mainWindow.setTitle(std::to_string(((double) frameCount) / (currentTime - previousTime)) + "FPS");
            previousTime = glfwGetTime();
            frameCount = 0;
        }
        ++frameCounterDebug;
    };

    return 0;
}
//
// Created by ekin4 on 28/04/2017.
//

#include "Constants.h"
#include "cogl.h"

int main() {
    cogl::GLWindow mainWindow(0);
    mainWindow.enableCapability(GL_DEPTH_TEST);
    mainWindow.enableCapability(GL_CULL_FACE);
    mainWindow.setCullType(GL_BACK);
    mainWindow.setDepthFunction(GL_LESS);
    mainWindow.setAASamples(0);

//    cogl::Mesh cube = cogl::Mesh::load_from_obj("dragon.obj");
    cogl::Mesh cube = cogl::Mesh::Cube;
    cube.setRenderType(cogl::RenderTypes::Tris);

    std::vector<cogl::Mesh> cubes(10000, cube);

    cogl::Camera defaultCamera = cogl::Camera(glm::vec3(5.0f, 5.0f, -5.0f),
                                              glm::vec3({0.f, 0.f, 0.f}),
                                              glm::vec3({0.0f, 1.0f, 0.0f}), cogl::projection::perspective);
    defaultCamera.changeAR(16.0 / 9.0);

    float radius = 4;
    float angle = 0.0;

    for (auto &i : cubes) {
        glm::vec3 dest = {glm::cos(angle), 0.0f, glm::sin(angle)};
        dest *= radius;
        i.scaleMesh(0.01, 1.0, 0.01);
        i.moveMeshTo(dest);
        angle += (float) (2 * PI / cubes.size());
    }

    defaultCamera.setEventHandling();

    cogl::Shader defShader("cogl/shaders/pointsTest");
    double previousTime = glfwGetTime();
    int frameCount = 0;

    while (!mainWindow.shouldClose()) {
        mainWindow.renderBegin();
        for (auto &i : cubes) {
            i.render(defShader, defaultCamera);
        }
#pragma omp parallel for
        for (auto i = 0; i < cubes.size(); ++i) {
            cubes[i].rotateMesh(PI * 0.001f, glm::vec3(0.0f, 1.0f, 0.0f));
        }
        mainWindow.renderEnd();
        double currentTime = glfwGetTime();
        frameCount++;
        if (currentTime - previousTime >= 1.0) {
            // Display the frame count here any way you want.
            mainWindow.setTitle(std::to_string(((double) frameCount) / (currentTime - previousTime)) + "FPS");
            previousTime = glfwGetTime();
            frameCount = 0;
        }
    };

    return 0;
}
//
// Created by ekin4 on 28/04/2017.
//

#include "Constants.h"
#include "cogl.h"

int main() {
    cogl::GLWindow mainWindow;
    mainWindow.enableCapability(GL_DEPTH_TEST);
    mainWindow.enableCapability(GL_CULL_FACE);
    mainWindow.setCullType(GL_BACK);
    mainWindow.setDepthFunction(GL_LESS);
    mainWindow.setAASamples(1);

    cogl::Mesh cube = cogl::Mesh::load_from_obj("dragon.obj");

    std::vector<cogl::Mesh> cubes;
    cubes.reserve(20);


    cube.setRenderType(cogl::RenderTypes::Tris);
    cogl::Camera defaultCamera = cogl::Camera(glm::vec3(5.0f, 5.0f, -5.0f),
                                              glm::vec3({0.f, 0.f, 0.f}),
                                              glm::vec3({0.0f, 1.0f, 0.0f}), cogl::projection::perspective);
    defaultCamera.changeAR(16.0 / 9.0);

    float radius = 4;
    float angle;

    for (auto i = 0; i < 10; ++i) {
        cubes.emplace_back(cube);

        angle = (float) (2 * i * PI / 10.0f);
        glm::vec3 dest = {glm::cos(angle), 0.0f, glm::sin(angle)};
        dest *= radius;
        cubes[i].scaleMesh(0.25);

        cubes[i].moveMeshTo(dest);
    }

    defaultCamera.setEventHandling();

    cogl::Shader defShader("cogl/shaders/pointsTest");

    while (!mainWindow.shouldClose()) {
        mainWindow.renderBegin();
        for (auto &&i : cubes) {
            i.render(defShader, defaultCamera);
            i.rotateMesh(PI * 0.001, glm::vec3(0.0f, 1.0f, 0.0f));
        }
        mainWindow.renderEnd();
    };

    return 0;
}
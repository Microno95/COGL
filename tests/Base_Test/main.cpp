//
// Created by ekin4 on 28/04/2017.
//

#include "../../Constants.h"
#include "../../cogl.h"

int main() {
    cogl::GLWindow mainWindow(1, 4, 0, 1, 3840, 2160);
    mainWindow.enableCapability(GL_VERTEX_PROGRAM_POINT_SIZE);
    mainWindow.enableCapability(GL_DEPTH_TEST);
    mainWindow.enableCapability(GL_CULL_FACE);
    mainWindow.setCullType(GL_BACK);
    mainWindow.setDepthFunction(GL_LESS);
    mainWindow.setAASamples(0);

    cogl::Mesh cube = cogl::Mesh::load_from_obj("dragon.obj");
    cogl::Mesh otherCube = cogl::Mesh::Cube;
    cogl::Vertex test1{0.0f, 0.0f, 0.0f};
    std::vector<cogl::Vertex> list{test1};
    cogl::Mesh test2(list);
    test2.setRenderType(cogl::RenderTypes::Points);

    cogl::MeshInstance cubes(cube, 2500);
    check_gl_error();

    cogl::Camera defaultCamera = cogl::Camera(glm::vec3(1.0f, 1.0f, 0.0f),
                                              glm::vec3({0.f, 0.f, 0.f}),
                                              glm::vec3({0.0f, 1.0f, 0.0f}), cogl::projection::perspective);
    defaultCamera.changeAR(16.0 / 9.0);
    defaultCamera.changeZFar(1000.0);
    defaultCamera.changeZNear(0.001);

    float radius = 3;
    float angle = 0.0;

    for (auto i = 0; i < cubes.activeInstances(); ++i) {
        glm::vec3 dest = {glm::cos(angle), 0.0f, glm::sin(angle)};
        dest *= radius;
        cubes.scaleMesh(i, 0.001, 0.001, 0.001);
        cubes.moveMeshTo(i, dest);
        angle += (float) (2 * PI / cubes.activeInstances());
    }

    defaultCamera.setEventHandling();

    cogl::Shader defShader("cogl/shaders/triTest");
    cogl::Shader solidShader("cogl/shaders/solidColour");
    double previousTime = glfwGetTime();
    int frameCount = 0;
    int frameCounterDebug = 0;
    glm::vec3 target_on_floor;

    while (!mainWindow.shouldClose()) {
        otherCube.moveMeshTo(target_on_floor);
        cubes.rotateMesh(-1, PI * 0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
        mainWindow.renderBegin();

        target_on_floor = defaultCamera.getCameraTargetPosition();
        std::cout << glm::to_string(target_on_floor) << std::endl;
        otherCube.render(solidShader, defaultCamera);
        cubes.render(defShader, defaultCamera);
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
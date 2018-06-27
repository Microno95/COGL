//
// Created by ekin4 on 28/04/2017.
//

#include "../../Constants.h"
#include "../../cogl.h"
#include <exception>

#include <cstdio>  /* defines FILENAME_MAX */

#include <direct.h>
#define GetCurrentDir _getcwd

std::string GetCurrentWorkingDir() {
    char cCurrentPath[FILENAME_MAX];

    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        throw std::runtime_error("Current Dir makes no sense");
    }

    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

    return cCurrentPath;
}

int main() {
    std::cout << GetCurrentWorkingDir() << std::endl;
    cogl::GLWindow mainWindow(1, 4, 5, 1, 1024, 768);
    mainWindow.enableCapability(GL_VERTEX_PROGRAM_POINT_SIZE);
    mainWindow.enableCapability(GL_DEPTH_TEST);
    mainWindow.enableCapability(GL_CULL_FACE);
    mainWindow.setCullType(GL_BACK);
    mainWindow.setDepthFunction(GL_LESS);
    mainWindow.setAASamples(1);

    cogl::Mesh cube = cogl::Mesh::load_from_obj("dragon.obj");

    cogl::Camera defaultCamera = cogl::Camera(glm::vec3(1.0f, 1.0f, 0.0f),
                                              glm::vec3({0.f, 0.f, 0.f}),
                                              glm::vec3({0.0f, 1.0f, 0.0f}), cogl::projection::perspective);
    defaultCamera.changeAR(16.0 / 9.0);
    defaultCamera.changeZFar(1000.0);
    defaultCamera.changeZNear(0.001);

    defaultCamera.setEventHandling();

    cogl::Shader defShader("cogl/shaders/triTest");
    check_gl_error();
    cogl::Shader solidShader("cogl/shaders/solidColour");
    check_gl_error();
    double previousTime = glfwGetTime();
    int frameCount = 0;
    int frameCounterDebug = 0;
	glm::vec3 target_on_floor{ 0.0,0.0,0.0 };
	float angular_speed = 0.025f;
	cube.scaleMesh(0.01f);
	cube.moveMeshTo(target_on_floor);

	std::cout << glm::to_string(defaultCamera.getMVPMatrix(cube.getModelMatrix())) << std::endl;

    while (!mainWindow.shouldClose()) {
		cube.rotateMesh(PI * angular_speed, glm::vec3(0.0f, 1.0f, 0.0f));
        mainWindow.renderBegin();
		cube.render(defShader, defaultCamera);
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
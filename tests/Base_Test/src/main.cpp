//
// Created by ekin4 on 28/04/2017.
//

#include <cogl/cogl.h>
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

    return std::string(cCurrentPath);
}

int main() {
    std::cout << GetCurrentWorkingDir() << std::endl;
    cogl::GLWindow mainWindow(0, 4, 5, 1, 1024, 768, 16, 9, "NULL", "data/postProcessing", false);
    mainWindow.enableCapability(GL_VERTEX_PROGRAM_POINT_SIZE);
	mainWindow.enableCapability(GL_PROGRAM_POINT_SIZE);
    mainWindow.enableCapability(GL_DEPTH_TEST);
    mainWindow.enableCapability(GL_CULL_FACE);
    mainWindow.setCullType(GL_BACK);
    mainWindow.setDepthFunction(GL_LESS);
    mainWindow.setAASamples(0);

    cogl::Mesh original_dragon = cogl::Mesh::load_from_obj("data/dragon.obj"), cube = cogl::Mesh::load_from_obj("data/dragon.obj");
	cube.scaleMesh(0.25f);

    cogl::Camera defaultCamera = cogl::Camera(glm::vec3(1.0f, 1.0f, 0.0f),
                                              glm::vec3({0.f, 0.f, 0.f}),
                                              glm::vec3({0.0f, 1.0f, 0.0f}), cogl::projection::perspective);
    defaultCamera.changeAR(16.0 / 9.0);
    defaultCamera.changeZFar(1000.0);
    defaultCamera.changeZNear(0.001);

	mainWindow.setMainCamera(defaultCamera);

    cogl::Shader defShader("data/triTest");
    check_gl_error();
    cogl::Shader solidShader("data/solidColour");
    check_gl_error();
    double previousTime = glfwGetTime();
	double otherPreviousTime = glfwGetTime();
	double reloadPeriod = 2.0;
    int frameCount = 0;
    int frameCounterDebug = 0;
	bool dragon_or_cube = false;
	glm::vec3 target_on_floor{ 0.0,0.0,0.0 };
	float angular_speed = 0.01f;

    while (!mainWindow.shouldClose()) {
		auto test = Timer<std::chrono::microseconds>("Frame Time", true, "us");
		cube.rotateMesh(PI * angular_speed, glm::vec3({0.0f, 1.0f, 0.0f}));
		if (previousTime - otherPreviousTime >= reloadPeriod) {
			auto load_test = Timer<std::chrono::microseconds>((dragon_or_cube ? "Dragon Load" : "Cube Load"), false, "us");
			if (dragon_or_cube) {
				cube = cogl::Mesh(original_dragon.getMeshRepresentation());
				dragon_or_cube = false;
			}
			else {
				cube = cogl::Mesh(cogl::MeshRepresentation::Cube);
				dragon_or_cube = true;
			}
			otherPreviousTime = glfwGetTime();
			cube.scaleMesh(0.25f);
		}
		cube.moveMeshTo(target_on_floor);
        mainWindow.renderBegin();
		cube.render(solidShader, defaultCamera, true);
        mainWindow.renderEnd();
		glFinish();
		test.Stop();
		double currentTime = glfwGetTime();
		if (currentTime - previousTime >= 1.0) {
			// Display the frame count here any way you want.
			mainWindow.setTitle("FPS: " + std::to_string(frameCount / (currentTime - previousTime)) + " | " + std::to_string(test.GetTimeDelta().count()) + "us | frame: " + std::to_string(frameCounterDebug));
			previousTime = glfwGetTime();
			frameCount = 0;
		}
        frameCount++;
        ++frameCounterDebug;
    };

    return 0;
}
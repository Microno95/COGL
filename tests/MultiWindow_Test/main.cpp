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

	auto initial_representation = cogl::MeshRepresentation::load_from_obj("dragon.obj");
	initial_representation.mergeRepresentations(cogl::MeshRepresentation::Cube);

	cogl::GLWindow mainWindow(0, 4, 5, 1, 1024, 768);
	mainWindow.enableCapability(GL_DEPTH_TEST);
	mainWindow.enableCapability(GL_CULL_FACE);
	mainWindow.setCullType(GL_BACK);
	mainWindow.setDepthFunction(GL_LESS);
	mainWindow.setAASamples(0);

	cogl::Camera defaultCamera = cogl::Camera(glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3({ 0.f, 0.f, 0.f }),
		glm::vec3({ 0.0f, 1.0f, 0.0f }), cogl::projection::perspective);
	defaultCamera.changeAR(16.0 / 9.0);
	defaultCamera.changeZFar(1000.0);
	defaultCamera.changeZNear(0.001);

	mainWindow.setMainCamera(defaultCamera);

	cogl::Mesh test_object = cogl::Mesh(initial_representation);

	cogl::Shader defShader("cogl/shaders/triTest");
	cogl::Shader solidShader("cogl/shaders/solidColour");

	cogl::GLWindow secWindow(1, 4, 5, 1, 1024, 768);
	secWindow.enableCapability(GL_DEPTH_TEST);
	secWindow.enableCapability(GL_CULL_FACE);
	secWindow.setCullType(GL_BACK);
	secWindow.setDepthFunction(GL_LESS);
	secWindow.setAASamples(2);

    cogl::Mesh test_object2 = cogl::Mesh(cogl::MeshRepresentation::Icosahedron);

	cogl::Camera secCamera = cogl::Camera(glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3({ 0.f, 0.f, 0.f }),
		glm::vec3({ 0.0f, 1.0f, 0.0f }), cogl::projection::perspective);
	secCamera.changeAR(16.0 / 9.0);
	secCamera.changeZFar(1000.0);
	secCamera.changeZNear(0.001);

	secWindow.setMainCamera(secCamera);

    cogl::Shader defShader2("cogl/shaders/triTest");
    cogl::Shader solidShader2("cogl/shaders/solidColour");

    int frameCount = 0;
    int frameCounterDebug = 0;
	auto mainTiming = 0, secTiming = 0;
	float angular_speed = 0.001f;

    while (!mainWindow.shouldClose() && !secWindow.shouldClose()) {
		Timer test = Timer("Frame Time", false);
		test_object.rotateMesh(PI * angular_speed, glm::vec3({ 0.0f, 1.0f, 0.0f }));
		test_object2.rotateMesh(PI * angular_speed, glm::vec3({ 0.0f, 1.0f, 0.0f }));
		Timer mainTimer = Timer("Frame Time for Main", true);
		mainWindow.setCurrentContext();
		mainWindow.renderBegin();
		test_object.render(defShader, defaultCamera, true);
		glFinish();
		mainWindow.renderEnd();
		mainTimer.Stop();
		Timer secTimer = Timer("Frame Time for Sec", true);
		secWindow.setCurrentContext();
		secWindow.renderBegin();
		test_object2.render(solidShader2, secCamera, true);
		secWindow.renderEnd();
		glFinish();
		secTimer.Stop();
		mainTiming += mainTimer.GetTimeDelta().count();
		secTiming += secTimer.GetTimeDelta().count();
		if (++frameCount > 2) {
			secTiming /= frameCount - 1;
			mainTiming /= frameCount - 1;
			// Display the frame count here any way you want.
			mainWindow.setTitle("FPS: " + std::to_string(1.0e3 / mainTiming) + " | " + std::to_string(mainTiming) + "ms | frame: " + std::to_string(frameCounterDebug));
			secWindow.setTitle("FPS: " + std::to_string(1.0e3 / secTiming) + " | " + std::to_string(secTiming) + "ms | frame: " + std::to_string(frameCounterDebug));
			mainTiming = 0;
			secTiming = 0;
			frameCount = 0;
		}
        ++frameCounterDebug;
    };

    return 0;
}
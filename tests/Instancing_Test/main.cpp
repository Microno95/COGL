//
// Created by ekin4 on 28/04/2017.
//

#include "../../Constants.h"
#include "../../cogl.h"

int main() {
	cogl::GLWindow mainWindow(1, 4, 5, 1, 1024, 768);
	mainWindow.enableCapability(GL_VERTEX_PROGRAM_POINT_SIZE);
	mainWindow.enableCapability(GL_PROGRAM_POINT_SIZE);
	mainWindow.enableCapability(GL_DEPTH_TEST);
	mainWindow.enableCapability(GL_CULL_FACE);
	mainWindow.setCullType(GL_BACK);
	mainWindow.setDepthFunction(GL_LESS);
	mainWindow.setAASamples(1);

	//cogl::MeshInstance cubes(cogl::Mesh::Cube, 25);
	//auto cube = cogl::Mesh::Cube;
	cogl::MeshInstance cube(cogl::Mesh::Cube, 1);


    float radius = 1;
    float angle = 0.0;

    /*for (auto i = 0; i < cubes.activeInstances(); ++i) {
		angle = i * (float)(2 * PI / cubes.activeInstances());
        glm::vec3 dest = {glm::cos(angle), 0.0f, glm::sin(angle)};
        dest *= radius;
		cubes.moveMeshTo(i, dest);
    }*/

	cube.scaleMesh(-1, 0.1f);

	cogl::Camera defaultCamera = cogl::Camera(glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3({ 0.f, 0.f, 0.f }),
		glm::vec3({ 0.0f, 1.0f, 0.0f }), cogl::projection::perspective);
	defaultCamera.changeAR(16.0 / 9.0);
	defaultCamera.changeZFar(1000.0);
	defaultCamera.changeZNear(0.001);

	defaultCamera.setEventHandling();

	cogl::Shader defShader("cogl/shaders/solidColour");

    double previousTime = glfwGetTime();
    int frameCount = 0;
    int frameCounterDebug = 0;

    while (!mainWindow.shouldClose()) {
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
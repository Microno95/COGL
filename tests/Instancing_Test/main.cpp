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
	mainWindow.setAASamples(0);

	//cogl::MeshInstance cubes(cogl::Mesh::Cube, 25);
	//auto cube = cogl::Mesh::Cube;
	cogl::MeshInstance cubes(cogl::Mesh::Cube, 10000);

    float radius = 3;
    float angle = 0.0;

	double dx = 0.1;
	int rowWidth = 24;

	for (auto i = 0; i < cubes.activeInstances(); ++i) {
		cubes.moveMeshTo(i, glm::vec3({ -1.0f * dx * (i / rowWidth - rowWidth / 2), 0.0f, dx * (i % rowWidth - rowWidth / 2)}));
	}

	cubes.scaleMesh(-1, 0.025f);

	cogl::Camera defaultCamera = cogl::Camera(glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3({ 0.f, 0.f, 0.f }),
		glm::vec3({ 0.0f, 1.0f, 0.0f }), cogl::projection::perspective);
	defaultCamera.changeAR(16.0 / 9.0);
	defaultCamera.changeZFar(1000.0);
	defaultCamera.changeZNear(0.001);

	defaultCamera.setEventHandling();

	cogl::Shader defShader("cogl/shaders/triTestInst");

    double previousTime = glfwGetTime();
	double currentTime = glfwGetTime();
    int frameCount = 0;
	int every_n_frames = 5;
	float rotation_speed = 0.001f;

    while (!mainWindow.shouldClose()) {
		Timer test = Timer("Frame Time");
		previousTime = glfwGetTime();
		cubes.rotateMesh(-1, 2 * PI * rotation_speed, glm::vec3({ 0.0f, 1.0f, 0.0f }));
		mainWindow.renderBegin();
		cubes.render(defShader, defaultCamera, false);
		mainWindow.renderEnd();
		currentTime = glfwGetTime();
        if (frameCount++ >= every_n_frames) {
            // Display the frame count here any way you want.
            mainWindow.setTitle(std::to_string(((currentTime - previousTime)) * 1e3) + "ms");
            frameCount = 0;
        }
    };

    return 0;
}
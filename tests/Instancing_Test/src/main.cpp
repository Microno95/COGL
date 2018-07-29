//
// Created by ekin4 on 28/04/2017.
//

#include <cogl/cogl.h>

class MyCamera : public cogl::Camera {
	using cogl::Camera::Camera;

public:
	bool swap_mesh = true;
	int frameCountDebug = 0;

	void keycallback(GLFWwindow *window, int key, int scancode,
		int action, int mods) override {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		double motionVel = 0.01f * getDistanceToTarget();
		glm::vec3 forward = glm::vec3({ 1.0f, 0.0f, 0.0f });
		glm::vec3 left = glm::vec3({ 0.0f, 0.0f, 1.0f });
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			moveCamera(motionVel * getCameraUp());
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)  {
			moveCamera(-motionVel * getCameraUp());
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			moveCamera(motionVel * getCameraLeft());
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			moveCamera(-motionVel * getCameraLeft());
		}
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			moveCameraTo(glm::vec3(1.0f));
			moveCameraTargetTo(glm::vec3(0.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			moveCamera(motionVel * forward);
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			moveCamera(-motionVel * forward);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			moveCameraTarget(motionVel * left);
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			moveCameraTarget(-motionVel * left);
		}
		if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS && mods == GLFW_MOD_SHIFT) {
			printf("add\n");
		}
		if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
			printf("subtract\n");
		}
		if (key == GLFW_KEY_F && action == GLFW_RELEASE) {
			printf("swapped\n");
			swap_mesh = !swap_mesh;
			frameCountDebug = 0;
		}
	}
};

int main() {
	cogl::GLWindow mainWindow(0, 4, 5, 1, 1024, 768, 16, 9, "NULL", "data/postProcessing", false);
	mainWindow.enableCapability(GL_VERTEX_PROGRAM_POINT_SIZE);
	mainWindow.enableCapability(GL_PROGRAM_POINT_SIZE);
	mainWindow.enableCapability(GL_DEPTH_TEST);
	mainWindow.enableCapability(GL_CULL_FACE);
	mainWindow.setCullType(GL_BACK);
	mainWindow.setDepthFunction(GL_LESS);
	mainWindow.setAASamples(4);

	//cogl::MeshInstance cubes(cogl::Mesh::Cube, 25);
	//auto cube = cogl::Mesh::Cube;
	cogl::MeshInstance cubes(cogl::MeshRepresentation::Cube, 200000),
					   dragons(cogl::Mesh::load_from_obj("data/dragon.obj"), 100);

    float radius = 20;

	double dx;
	int rowWidth = 160;
	dx = radius / rowWidth;

	for (auto i = 0; i < cubes.activeInstances(); ++i) {
		cubes.moveMeshTo(i, glm::vec3({ -1.0f * dx * (i / rowWidth - rowWidth / 2), 0.0f, dx * (i % rowWidth - rowWidth / 2) }));
	}

	cubes.scaleMesh(-1, 0.025f);

	rowWidth = 5;
	dx = radius / rowWidth;

	for (auto i = 0; i < dragons.activeInstances(); ++i) {
		dragons.moveMeshTo(i, glm::vec3({ -1.0f * dx * (i / rowWidth - rowWidth / 2), 0.0f, dx * (i % rowWidth - rowWidth / 2) }));
	}

	dragons.scaleMesh(-1, 0.025f);

	std::cout << cubes.activeInstances() * cubes.getMeshRepresentation().vertices.size() << std::endl;
	std::cout << dragons.activeInstances() * dragons.getMeshRepresentation().vertices.size() << std::endl;

	MyCamera defaultCamera = MyCamera(glm::vec3({1.0f, 1.0f, 0.0f}),
		glm::vec3({ 0.f, 0.f, 0.f }),
		glm::vec3({ 0.0f, 1.0f, 0.0f }), cogl::projection::perspective);
	defaultCamera.changeAR(16.0 / 9.0);
	defaultCamera.changeZFar(1000.0);
	defaultCamera.changeZNear(0.001);

	mainWindow.setMainCamera(defaultCamera);

	cogl::Shader defShader("data/triTest");
    int frameCount = 0;
	int every_n_frames = 5;
	float rotation_speed = 0.01f;

    while (!mainWindow.shouldClose()) {
		auto test = Timer<>("Frame Time", true);
        glFinish();
		cubes.rotateMesh(-1, 2 * PI * rotation_speed, glm::vec3({ 0.0f, 1.0f, 0.0f }));
		mainWindow.renderBegin();
		if (defaultCamera.swap_mesh) {
			cubes.render(defShader, defaultCamera, true);
		}
		else {
			dragons.render(defShader, defaultCamera, true);
		}
		mainWindow.renderEnd();
        glFinish();
		test.Stop();
        if (frameCount++ >= every_n_frames) {
            // Display the frame count here any way you want.
            mainWindow.setTitle(std::to_string(test.GetTimeDelta().count()) + "ms");
            frameCount = 0;
        }
    };

    return 0;
}
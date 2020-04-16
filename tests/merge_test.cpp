//
// Created by ekin4 on 28/04/2017.
//

#include <cogl/cogl.h>
#include <exception>

#include <cstdio>  /* defines FILENAME_MAX */

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

std::string get_current_dir() {
    char buff[FILENAME_MAX]; //create string buffer to hold path
    GetCurrentDir( buff, FILENAME_MAX );
    std::string current_working_dir(buff);
    return current_working_dir;
}

int main() {
    std::cout << get_current_dir() << std::endl;
    cogl::GLWindow mainWindow(0, 4, 5, 1, 1024, 768, 16, 9, "NULL", "data/postProcessing", false);
    mainWindow.enableCapability(GL_VERTEX_PROGRAM_POINT_SIZE);
	mainWindow.enableCapability(GL_PROGRAM_POINT_SIZE);
    mainWindow.enableCapability(GL_DEPTH_TEST);
    mainWindow.enableCapability(GL_CULL_FACE);
    mainWindow.setCullType(GL_BACK);
    mainWindow.setDepthFunction(GL_LESS);
    mainWindow.setAASamples(0);

	auto initial_representation = cogl::MeshRepresentation::load_from_obj("data/dragon.obj");
    initial_representation.mergeRepresentations(cogl::MeshRepresentation::Cube, glm::translate(glm::vec3{1.0f, -1.0f, 0.0f}));

    float radius = 1;
    float angle = 0.0;

    double dx;
    glm::mat4 transform_matrix{0.0f};
    int rowWidth = 5, totnum = 10;
    dx = radius / rowWidth;

    for (auto i = 0; i < totnum; ++i) {
        transform_matrix = glm::translate(glm::vec3{ -1.0f * dx * (i / rowWidth - rowWidth / 2), 0.0f, dx * (i % rowWidth - rowWidth / 2) });
        transform_matrix = glm::rotate(static_cast<float>(0.1f * i * PI), glm::vec3{0.0f, 1.0f, 0.0f}) * transform_matrix;
        initial_representation.mergeRepresentations(initial_representation, transform_matrix);
    }

    cogl::Mesh test_object = cogl::Mesh(initial_representation);

    std::cout << test_object.getMeshRepresentation().vertices.size() << " vertices" << std::endl;

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
	float angular_speed = 0.001f;

    while (!mainWindow.shouldClose()) {
		test_object.rotateMesh(PI * angular_speed, glm::vec3({0.0f, 1.0f, 0.0f}));
        auto test = Timer<>("Frame Time", true);
		mainWindow.renderBegin();
		test_object.render(defShader, defaultCamera, true);
        mainWindow.renderEnd();
        glFinish();
        test.Stop();
		double currentTime = glfwGetTime();
		if (currentTime - previousTime >= 1.0) {
			// Display the frame count here any way you want.
			mainWindow.setTitle("FPS: " + std::to_string(frameCount / (currentTime - previousTime)) + " | " + std::to_string(test.GetTimeDelta().count()) + "ms | frame: " + std::to_string(frameCounterDebug));
			previousTime = glfwGetTime();
			frameCount = 0;
		}
        frameCount++;
        ++frameCounterDebug;
    };

    return 0;
}
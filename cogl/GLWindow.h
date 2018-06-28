//
// Created by ekin4 on 26/02/2017.
//

#ifndef IDEK_SCENEMANAGEMENT_H
#define IDEK_SCENEMANAGEMENT_H

#include "Shader.h"
#include "Camera.h"
#include "Renderable.h"
#include "Framebuffer.h"
#include "StateBaseGLWindow.h"
#include "../Constants.h"

namespace cogl {

    class GLWindow : public StateBaseGLWindow {
    protected:
        // Stored handle to current context //
        GLFWwindow *contextHandle;

        // Store the parameters of the current context //
        int swapInterval, aaSamples, contextMajor, contextMinor,
                windowWidth, windowHeight, aspectRatioWidth, aspectRatioHeight;
        std::string windowTitle;
		std::vector<GLenum> enabled_capabilities;

        // Framebuffers for postprocessing //
        GLuint quad_vertexbuffer, quad_indexbuffer, quad_vao;
        std::unique_ptr<Shader> postProcessingShader;
        std::unique_ptr<Framebuffer> nonMSFBO;
        std::unique_ptr<FramebufferMultisampled> MSFBO;
        glm::vec3 g_quad_vertex_buffer_data[4] = {glm::vec3(-1.0f, -1.0f, 0.0f),
                                                  glm::vec3(1.0f, -1.0f, 0.0f),
                                                  glm::vec3(1.0f, 1.0f, 0.0f),
                                                  glm::vec3(-1.0f, 1.0f, 0.0f)};
        GLint g_quad_vertex_buffer_indices[6] = {2, 1, 0, 0, 3, 2};

        // Protect window parameters during runtime //
        std::mutex paramLock;
        bool windowCreated = false;

    public:
        explicit GLWindow(int _swapInterval = 1, int _contextMajor = 4,
                 int _contextMinor = 3, int _aaSamples = 1, int _windowWidth = 1280, int _windowHeight = 720,
                 int _aspectRatioWidth = 16, int _aspectRatioHeight = 9,
                 std::string _windowTitle = "NULL", std::string pps_file = "cogl/shaders/postProcessing",
                 bool fullscreen = false);

        GLWindow(GLWindow const &) = delete;

        GLWindow(GLWindow &&) = delete;

        ~GLWindow();

        GLFWwindow *&operator*() { return contextHandle; }

        GLWindow &operator=(const GLWindow &) = delete;

        GLWindow &operator=(GLWindow &&) = delete;

        void setCurrentContext() {
            if (glfwGetCurrentContext() != contextHandle) glfwMakeContextCurrent(contextHandle);
        };

        bool isCurrentContext() { return (glfwGetCurrentContext() == contextHandle); }

        void terminateWindow();

        int shouldClose();

        void setKeyCallback(GLFWkeyfun key_callback);

        void setCursorPosCallback(GLFWcursorposfun key_callback);

        void setScrollCallback(GLFWscrollfun scroll_callback);

        void handleResizing();

        void setWidth(int width);

        void setHeight(int height);

        void setAspectRatioWidth(int arw) {
            aspectRatioWidth = arw;
            glfwSetWindowAspectRatio(contextHandle, aspectRatioWidth, aspectRatioHeight);
        }

        void setAspectRatioHeight(int arh) {
            aspectRatioHeight = arh;
            glfwSetWindowAspectRatio(contextHandle, aspectRatioWidth, aspectRatioHeight);
        };

        void setAASamples(int aas);

        void setTitle(std::string title);

        void setTitle(const char *title);

        void renderBegin();

        void renderEnd();

        // Convenience functions to enable and disable context capabilities //
        bool enableCapability(GLenum Capability);

        bool disableCapability(GLenum Capability);

        bool setDepthFunction(GLenum depthFunc);

        bool setCullType(GLenum mode);
        // ---------------------------------------------------------------- //

        static void error_callback(int error, const char *description);

        void windowsizecallback(GLFWwindow *window, int width, int height) override;

        void renderFramebuffers();
    };

}
#endif //IDEK_SCENEMANAGEMENT_H

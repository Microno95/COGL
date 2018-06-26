//
// Created by ekin4 on 30/04/2017.
//

#ifndef CUSTOMOGL_FRAMEBUFFER_H
#define CUSTOMOGL_FRAMEBUFFER_H

#include "../Constants.h"

namespace cogl {

    class Framebuffer {
    public:
        GLuint framebuffer = 0;
        GLuint colorBuffers = 0;
        GLuint depthRenderBuffer = 0;
        int width = 0, height = 0;

        explicit Framebuffer(int windowWidth = 1024, int windowHeight = 1024);

        ~Framebuffer();

        void generateFBO();

        void generateColorBuffer(int windowWidth, int windowHeight);

        void generateRenderBuffer(int windowWidth, int windowHeight);

        void regenerateBuffers(int windowWidth, int windowHeight) {
            width = windowWidth;
            height = windowHeight;
            generateColorBuffer(windowWidth, windowHeight);
            generateRenderBuffer(windowWidth, windowHeight);
        };

        void viewport() {
            glViewport(0, 0, width, height);
        }

        void clearFBO(GLfloat red = 0.0f, GLfloat green = 0.0f, GLfloat blue = 0.0f, GLfloat alpha = 1.0f);

        void bindFBO();

        void unbindFBO();

        void bindFBORead();

        void bindFBODraw();
    };

    class FramebufferMultisampled {
    public:
        GLuint framebuffer = 0;
        GLuint colorBuffers = 0;
        GLuint depthRenderBuffer = 0;
        int width = 0, height = 0, numAAs = 0;

        explicit FramebufferMultisampled(int aaSamples = 1, int windowWidth = 1024, int windowHeight = 1024);

        ~FramebufferMultisampled();

        void generateFBO();

        void generateColorBuffer(int aaSamples, int windowWidth, int windowHeight);

        void generateRenderBuffer(int aaSamples, int windowWidth, int windowHeight);

        void regenerateBuffers(int aaSamples, int windowWidth, int windowHeight) {
            width = windowWidth;
            height = windowHeight;
            numAAs = aaSamples;
            generateColorBuffer(numAAs, windowWidth, windowHeight);
            generateRenderBuffer(numAAs, windowWidth, windowHeight);
        };

        void viewport() {
            glViewport(0, 0, width, height);
        }

        void clearFBO(GLfloat red = 0.0f, GLfloat green = 0.0f, GLfloat blue = 0.0f, GLfloat alpha = 1.0f);

        void bindFBO();

        void unbindFBO();

        void bindFBORead();

        void bindFBODraw();

        void blitToBuffer(Framebuffer &other);

        void blitToBuffer(GLuint other);
    };

}

#endif //CUSTOMOGL_FRAMEBUFFER_H

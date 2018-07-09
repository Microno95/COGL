//
// Created by ekin4 on 30/04/2017.
//

#ifndef CUSTOMOGL_FRAMEBUFFER_H
#define CUSTOMOGL_FRAMEBUFFER_H

#include "../Constants.h"
#include "Shader.h"

namespace cogl {

    class Framebuffer {
    public:
        GLuint framebuffer = 0;
        GLuint colorBuffers = 0;
        GLuint depthRenderBuffer = 0;
        int width = 0, height = 0;

        explicit Framebuffer(int windowWidth = 1024, int windowHeight = 1024);

        //Delete the copy constructor/assignment.
        Framebuffer(const Framebuffer &) = delete;
        Framebuffer &operator=(const Framebuffer &) = delete;

        Framebuffer(Framebuffer &&other) noexcept;

        Framebuffer &operator=(Framebuffer &&other) noexcept;

        ~Framebuffer();

        void release();

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

        void bindFBOColorBufferToTexture(GLenum textureID, GLuint bindLocation) {
            glUniform1i(bindLocation, /*GL_TEXTURE*/ textureID - GL_TEXTURE0);
            glActiveTexture(textureID);
            glBindTexture(GL_TEXTURE_2D, colorBuffers);
        }

        void bindFBODepthStencilBufferToTexture(GLenum textureID, GLuint bindLocation) {
            glUniform1i(bindLocation, /*GL_TEXTURE*/ textureID - GL_TEXTURE0);
            glActiveTexture(textureID);
            glBindTexture(GL_TEXTURE_2D, depthRenderBuffer);
        }
    };

    class FramebufferMultisampled {
    public:
        GLuint framebuffer = 0;
        GLuint colorBuffers = 0;
        GLuint depthRenderBuffer = 0;
        int width = 0, height = 0, numAAs = 0;

        explicit FramebufferMultisampled(int aaSamples = 1, int windowWidth = 1024, int windowHeight = 1024);

        FramebufferMultisampled(FramebufferMultisampled &&other) noexcept;

        FramebufferMultisampled &operator=(FramebufferMultisampled &&other) noexcept;

        ~FramebufferMultisampled();

        void release();

        void generateFBO();

        void generateColorBuffer(int aaSamples, int windowWidth, int windowHeight);

        void generateRenderBuffer(int aaSamples, int windowWidth, int windowHeight);

        void regenerateBuffers(int aaSamples, int windowWidth, int windowHeight) {
            generateColorBuffer(aaSamples, windowWidth, windowHeight);
            generateRenderBuffer(aaSamples, windowWidth, windowHeight);
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

        void bindFBOColorBufferToTexture(GLenum textureID, GLuint bindLocation) {
            glUniform1i(bindLocation, /*GL_TEXTURE*/ textureID - GL_TEXTURE0);
            glActiveTexture(textureID);
            glBindTexture(GL_TEXTURE_2D, colorBuffers);
        }

        void bindFBODepthStencilBufferToTexture(GLenum textureID, GLuint bindLocation) {
            glUniform1i(bindLocation, /*GL_TEXTURE*/ textureID - GL_TEXTURE0);
            glActiveTexture(textureID);
            glBindTexture(GL_TEXTURE_2D, depthRenderBuffer);
        }
    };

}

#endif //CUSTOMOGL_FRAMEBUFFER_H

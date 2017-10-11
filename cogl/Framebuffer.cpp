//
// Created by ekin4 on 30/04/2017.
//

#include "Framebuffer.h"

cogl::Framebuffer::Framebuffer(int windowWidth, int windowHeight) {
    width = windowWidth;
    height = windowHeight;
    generateFBO();
    generateColorBuffer(windowWidth, windowHeight);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffers, 0);
    generateRenderBuffer(windowWidth, windowHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer);
    GLenum DrawBuffers = GL_COLOR_ATTACHMENT0;
    glDrawBuffers(1, &DrawBuffers);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

cogl::Framebuffer::~Framebuffer() {
    glDeleteTextures(1, &colorBuffers);
    glDeleteRenderbuffers(1, &depthRenderBuffer);
    glDeleteFramebuffers(1, &framebuffer);
}

void cogl::Framebuffer::generateFBO() {
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glGenTextures(1, &colorBuffers);
    glGenRenderbuffers(1, &depthRenderBuffer);
}

void cogl::Framebuffer::generateColorBuffer(int windowWidth, int windowHeight) {
    glBindTexture(GL_TEXTURE_2D, colorBuffers);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, windowWidth, windowHeight, 0, GL_RGBA, GL_FLOAT, NULL);
    glObjectLabel(GL_TEXTURE, colorBuffers, -1, "Example Texture");
    glBindTexture(GL_TEXTURE_2D, 0);
}

void cogl::Framebuffer::generateRenderBuffer(int windowWidth, int windowHeight) {
    glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowWidth, windowHeight);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void cogl::Framebuffer::clearFBO(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void cogl::Framebuffer::bindFBO() {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
}

void cogl::Framebuffer::unbindFBO() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void cogl::Framebuffer::bindFBORead() {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
}

void cogl::Framebuffer::bindFBODraw() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
}

cogl::FramebufferMultisampled::FramebufferMultisampled(int aaSamples, int windowWidth, int windowHeight) {
    width = windowWidth;
    height = windowHeight;
    numAAs = aaSamples;
    generateFBO();
    generateColorBuffer(aaSamples, windowWidth, windowHeight);
    generateRenderBuffer(aaSamples, windowWidth, windowHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorBuffers);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer);
    GLenum DrawBuffers = GL_COLOR_ATTACHMENT0;
    glDrawBuffers(1, &DrawBuffers);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

cogl::FramebufferMultisampled::~FramebufferMultisampled() {
    glDeleteRenderbuffers(1, &colorBuffers);
    glDeleteRenderbuffers(1, &depthRenderBuffer);
    glDeleteFramebuffers(1, &framebuffer);
}

void cogl::FramebufferMultisampled::generateFBO() {
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glGenRenderbuffers(1, &depthRenderBuffer);
    glGenRenderbuffers(1, &colorBuffers);
}

void cogl::FramebufferMultisampled::generateColorBuffer(int aaSamples, int windowWidth, int windowHeight) {
    glBindRenderbuffer(GL_RENDERBUFFER, colorBuffers);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, aaSamples, GL_RGBA16F, windowWidth, windowHeight);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void cogl::FramebufferMultisampled::generateRenderBuffer(int aaSamples, int windowWidth, int windowHeight) {
    glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, aaSamples, GL_DEPTH24_STENCIL8, windowWidth, windowHeight);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void cogl::FramebufferMultisampled::clearFBO(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void cogl::FramebufferMultisampled::bindFBO() {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
}

void cogl::FramebufferMultisampled::unbindFBO() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void cogl::FramebufferMultisampled::bindFBORead() {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
}

void cogl::FramebufferMultisampled::bindFBODraw() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
}

void cogl::FramebufferMultisampled::blitToBuffer(cogl::Framebuffer &other) {
    bindFBORead();
    other.bindFBODraw();
    other.viewport();
    other.clearFBO();
    glBlitFramebuffer(0, 0, width, height,
                      0, 0, other.width, other.height,
                      GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
}

void cogl::FramebufferMultisampled::blitToBuffer(GLuint other) {
    assert(glIsFramebuffer(other) || other == 0);
    bindFBORead();
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, other);
    int widthOther, heightOther;
    glGetRenderbufferParameteriv(GL_RENDERBUFFER_WIDTH, GL_RENDERBUFFER, &widthOther);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER_HEIGHT, GL_RENDERBUFFER, &heightOther);
    glBlitFramebuffer(0, 0, width, height,
                      0, 0, widthOther, heightOther,
                      GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

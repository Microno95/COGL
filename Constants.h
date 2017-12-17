//
// Created by ekin4 on 28/04/2017.
//

#ifndef __gl_h_
#include <glad/glad.h>

#endif

#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtc/random.hpp>
#include <glm/ext.hpp>
#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <mutex>
#include <memory>
#include <sstream>

#ifndef CUSTOMOGL_CONSTANTS_H
#define CUSTOMOGL_CONSTANTS_H

#define check_gl_error_w(data) _check_gl_error(__FILE__,__LINE__, data)
#define check_gl_error() _check_gl_error(__FILE__,__LINE__)
#define check_fbo_status() _check_fbo_status(__FILE__,__LINE__)

static void _check_gl_error(const char *file, int line, int additional_data = 0) {
    GLenum errNum = glGetError();
    while (errNum != GL_NO_ERROR) {
        std::string error;

        switch (errNum) {
            case GL_INVALID_OPERATION:
                error = "INVALID_OPERATION";
                break;
            case GL_INVALID_ENUM:
                error = "INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                error = "INVALID_VALUE";
                break;
            case GL_OUT_OF_MEMORY:
                error = "OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error = "INVALID_FRAMEBUFFER_OPERATION";
                break;
            default:
                break;
        }

        std::cerr << additional_data << " | GL_" << error.c_str() << " - " << file << ":" << line << std::endl;
        errNum = glGetError();
    }
}

static void _check_fbo_status(const char *file, int line) {
    std::string fboStatus;
    switch (glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
        default:
            break;
        case GL_FRAMEBUFFER_COMPLETE:
            fboStatus = "Framebuffer Complete";
            break;
        case GL_FRAMEBUFFER_UNDEFINED:
            fboStatus = "Framebuffer Undefined";
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            fboStatus = "Framebuffer Incomplete Read Buffer";
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            fboStatus = "Framebuffer Incomplete Multisample";
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            fboStatus = "incomplete attachment";
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
            fboStatus = "incomplete dimensions";
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            fboStatus = "incomplete missing attachment";
            break;
        case GL_FRAMEBUFFER_UNSUPPORTED:
            fboStatus = "framebuffer unsupported";
            break;
    }
    std::cerr << fboStatus << " - " << file << ":" << line << std::endl;
}

constexpr double PI = 3.141592653589793238462643383279502884197169399375105820975;
constexpr double sqrt2 = 1.414213562373095048801688724209698078569671875376948073176;

#endif //CUSTOMOGL_CONSTANTS_H

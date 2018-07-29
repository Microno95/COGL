//
// Created by ekin4 on 28/04/2017.
//

#include <glad/glad.h>

#define GLM_ENABLE_EXPERIMENTAL

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
#include <chrono>

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

namespace cogl {
    namespace utilities {

        /*

        Contains function to test if container contains an element.
        Source: https://codereview.stackexchange.com/a/59999

        */
        template<class C, class T>
        inline auto contains(const C& v, const T& x)
        -> decltype(std::end(v), true)
        {
            return std::end(v) != std::find(std::begin(v), std::end(v), x);
        }

        template<class T = std::chrono::milliseconds>
        class Timer {
        private:
            std::string label = "", suffix = "ms";
            std::chrono::high_resolution_clock::time_point startTime;
            std::chrono::high_resolution_clock::time_point stopTime;
            bool stopTimeSet = false;
            bool suppressReportOnDestruct = false;

        public:
            Timer(std::string _suffix = "ms") : suffix(_suffix) {
                startTime = std::chrono::high_resolution_clock::now();
            }
            Timer(std::string _label, std::string _suffix = "ms") : label(_label), startTime(std::chrono::high_resolution_clock::now()), suffix(_suffix) {}
            Timer(std::string _label, bool _suppressReportOnDestruct, std::string _suffix = "ms") : label(_label), startTime(std::chrono::high_resolution_clock::now()), suppressReportOnDestruct(_suppressReportOnDestruct), suffix(_suffix) {}

            ~Timer() {
                if (!stopTimeSet) {
                    stopTime = std::chrono::high_resolution_clock::now();
                }
                if (!suppressReportOnDestruct) std::cout << label << " : " << std::chrono::duration_cast<T>(stopTime - startTime).count() << suffix << std::endl;
            }

            void Stop() {
                stopTime = std::chrono::high_resolution_clock::now();
                stopTimeSet = true;
            }

            void Start() {
                startTime = std::chrono::high_resolution_clock::now();
                stopTimeSet = false;
            }

            void Report() {
                std::cout << label << " : " << std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now() - startTime).count() << suffix << std::endl;
            }

            T GetTimeDeltaNow() {
                return std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now() - startTime);
            }

            T GetTimeDelta() {
                return std::chrono::duration_cast<T>(stopTime - startTime);
            }
        };

        inline std::vector<std::string> split_string(const std::string& s, const std::string& delim, const bool keep_empty = true) {
            std::vector<std::string> result;
            if (delim.empty()) {
                result.push_back(s);
                return result;
            }
            std::string::const_iterator subend;
            for (std::string::const_iterator substart = s.begin(); subend != s.end(); substart = subend + delim.size()) {
                subend = std::search(substart, s.end(), delim.begin(), delim.end());
                std::string temp(substart, subend);
                if (keep_empty || !temp.empty()) {
                    result.push_back(temp);
                }
                substart = subend + delim.size();
            }
            return result;
        };

        template<class TContainer>
        inline bool begins_with(const TContainer& input, const TContainer& match)
        {
            return input.size() >= match.size()
                   && std::equal(std::begin(match), std::end(match), std::begin(input));
        };
    }
}

#endif //CUSTOMOGL_CONSTANTS_H

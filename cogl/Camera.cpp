//
// Created by ekin4 on 24/02/2017.
//

#include "Camera.h"

namespace cogl {
    Camera::Camera(projection proj) {
        selfProj = proj;
        camPos = glm::vec3({0.0f, 0.0f, 1.0f});
        camTarget = glm::vec3({0.0f, 0.0f, 0.0f});
        camUp = glm::vec3({0.0f, 1.0f, 0.0f});
        computeViewMatrix();
        computeProjectionMatrix();
    }

    Camera::Camera(const glm::vec3 &cameraPosition, const glm::vec3 &cameraTarget, const glm::vec3 &cameraUp,
                   projection proj) {
        selfProj = proj;
        camPos = glm::vec3(cameraPosition);
        camTarget = glm::vec3(cameraTarget);
        camUp = glm::vec3(cameraUp);
        computeViewMatrix();
        computeProjectionMatrix();
    }

    Camera::Camera(double fieldOfView, double aspectRatio, double zNear, double zFar, const glm::vec3 &camPos,
                   const glm::vec3 &camTarget, const glm::vec3 &camUp, projection proj) : fieldOfView(fieldOfView),
                                                                                          aspectRatio(aspectRatio),
                                                                                          zNear(zNear), zFar(zFar),
                                                                                          camPos(camPos),
                                                                                          camTarget(camTarget),
                                                                                          camUp(camUp) {
        selfProj = proj;
        computeViewMatrix();
        computeProjectionMatrix();
    }

    Camera &Camera::moveCamera(const glm::vec3 &translation) {
        camPos += translation;
        computeViewMatrix();
        return *this;
    }

    Camera &Camera::moveCameraTarget(const glm::vec3 &translation) {
        camTarget += translation;
        computeViewMatrix();
        return *this;
    }

    Camera &Camera::rotateCamera(const double &angle, const glm::vec3 &center, const glm::vec3 &axisOfRotation,
                                 const angUnits units) {
        camPos = center + glm::mat3x3(glm::rotate((float) (units == angUnits::radians ? 180.0f * angle / PI : angle),
                                                  axisOfRotation)) * (camPos - center);
        computeViewMatrix();

        return *this;
    }

    Camera &Camera::rotateCamera(const double &angle, const glm::vec3 &axisOfRotation,
                                 const angUnits units) {
        camPos = glm::mat3x3(glm::rotate((float) (units == angUnits::radians ? 180.0f * angle / PI : angle),
                                         axisOfRotation)) * camPos;
        computeViewMatrix();

        return *this;
    }

    Camera &Camera::changeFoV(const double &fov) {
        fieldOfView = fov;
        computeProjectionMatrix();
        return *this;
    }

    Camera &Camera::changeZFar(const double &zf) {
        zFar = zf;
        computeProjectionMatrix();
        return *this;
    }

    Camera &Camera::changeZNear(const double &zn) {
        zNear = zn;
        computeProjectionMatrix();
        return *this;
    }

    Camera &Camera::moveCameraTo(const glm::vec3 &translation) {
        camPos = translation;
        computeViewMatrix();
        return *this;
    }

    Camera &Camera::moveCameraTargetTo(const glm::vec3 &translation) {
        camTarget = translation;
        computeViewMatrix();
        return *this;
    }

    void Camera::computeViewMatrix() {
        viewMatrix = glm::lookAt(camPos, camTarget, camUp);
    }

    Camera &Camera::changeAR(const double &ar) {
        aspectRatio = ar;
        computeProjectionMatrix();
        return *this;
    }

    void Camera::computeProjectionMatrix() {
        if (selfProj == projection::perspective) {
            projMatrix = glm::perspective(fieldOfView, aspectRatio, zNear, zFar);
        } else {
            projMatrix = glm::ortho(-fieldOfView * aspectRatio, fieldOfView * aspectRatio,
                                    -fieldOfView, fieldOfView, zNear, zFar);
        }
    }


    void Camera::keycallback(GLFWwindow *window, int key, int scancode,
                             int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        double motionVel = 0.01f * getDistanceToTarget();
        glm::vec3 forward = glm::vec3({1.0f, 0.0f, 0.0f});
        glm::vec3 left = glm::vec3({0.0f, 0.0f, 1.0f});
        if (key == GLFW_KEY_W) {
            moveCamera(motionVel * getCameraUp());
        }
        if (key == GLFW_KEY_S) {
            moveCamera(-motionVel * getCameraUp());
        }
        if (key == GLFW_KEY_A) {
            moveCamera(motionVel * getCameraLeft());
        }
        if (key == GLFW_KEY_D) {
            moveCamera(-motionVel * getCameraLeft());
        }
        if (key == GLFW_KEY_R) {
            moveCameraTo(glm::vec3(5.0f));
            moveCameraTargetTo(glm::vec3(0.0f));
        }
        if (key == GLFW_KEY_UP) {
            moveCamera(motionVel * forward);
        }
        if (key == GLFW_KEY_DOWN) {
            moveCamera(-motionVel * forward);
        }
        if (key == GLFW_KEY_LEFT) {
            moveCameraTarget(motionVel * left);
        }
        if (key == GLFW_KEY_RIGHT) {
            moveCameraTarget(-motionVel * left);
        }
    }

    void Camera::scrollcallback(GLFWwindow *window, double xoffset, double yoffset) {
        moveCamera(0.1f * yoffset * getCameraForward() * pow(getDistanceToTarget(), 1.0 / 2.0));
    }
}

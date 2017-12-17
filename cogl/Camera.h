//
// Created by ekin4 on 24/02/2017.
//

#ifndef IDEK_CAMERA_H
#define IDEK_CAMERA_H

#include "../Constants.h"
#include "StateBase.h"

namespace cogl {
    enum projection {
        perspective, orthographic
    };
    enum angUnits {
        radians, degrees
    };

    class Camera : public StateBase {
    private:
        double fieldOfView = 45.0f, aspectRatio = 1.0f, zNear = 0.05f, zFar = 100.0f;
        projection selfProj = projection::perspective;
        glm::vec3 camPos, camTarget, camUp;
        glm::mat4x4 projMatrix, viewMatrix;
    public:
        Camera(projection proj = projection::perspective);

        Camera(const glm::vec3 &cameraPosition, const glm::vec3 &cameraTarget, const glm::vec3 &cameraUp,
               projection proj = projection::perspective);

        Camera(double fieldOfView, double aspectRatio, double zNear, double zFar, const glm::vec3 &camPos,
               const glm::vec3 &camTarget, const glm::vec3 &camUp, projection proj = projection::perspective);


        Camera &moveCamera(const glm::vec3 &translation);

        Camera &moveCameraTo(const glm::vec3 &translation);

        Camera &moveCameraTarget(const glm::vec3 &translation);

        Camera &moveCameraTargetTo(const glm::vec3 &translation);

        Camera &rotateCamera(const double &angle, const glm::vec3 &center, const glm::vec3 &axisOfRotation,
                             const angUnits units = angUnits::radians);

        Camera &
        rotateCamera(const double &angle, const glm::vec3 &axisOfRotation, const angUnits units = angUnits::radians);

        Camera &changeFoV(const double &fov);

        Camera &changeAR(const double &ar);

        Camera &changeAspectRatio(const double &ar) {
            return changeAR(ar);
        };

        Camera &changeZFar(const double &zf);

        Camera &changeZNear(const double &zn);

        glm::mat4x4 getPMatrix() const {
            return (glm::mat4x4(projMatrix));
        }

        glm::mat4x4 getVMatrix() const {
            return (glm::mat4x4(viewMatrix));
        }

        glm::mat4x4 getVPMatrix() const {
            return (projMatrix * viewMatrix);
        }

        glm::mat4x4 getMVPMatrix(const glm::mat4x4 m) const {
            return (projMatrix * viewMatrix * m);
        }

        glm::vec3 getCameraUp() const {
            return glm::normalize(camUp);
        }

        glm::vec3 getCameraForward() const {
            return glm::normalize((camTarget - camPos));
        }

        glm::vec3 getCameraLeft() const {
            return glm::normalize(glm::cross(camUp, (camTarget - camPos)));
        }

        float getDistanceToTarget() const {
            float result = glm::distance(camPos, camTarget);
            return result;
        }

        glm::vec3 getCameraPosition() const {
            return camPos;
        }

        glm::vec3 getCameraTargetPosition() const {
            return camTarget;
        }

        void computeViewMatrix();

        void computeProjectionMatrix();

        virtual void keycallback(
                GLFWwindow *window,
                int key,
                int scancode,
                int action,
                int mods);

        virtual void scrollcallback(
                GLFWwindow *window,
                double xoffset, double yoffset);

    };
}
#endif //IDEK_CAMERA_H

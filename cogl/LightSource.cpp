//
// Created by ekin4 on 26/02/2017.
//

#include "LightSource.h"

namespace cogl {

    LightSource::LightSource(const Mesh *otherAppearance, const glm::vec3 &lightDir, const glm::vec3 &lightPos,
                             const glm::vec3 &lightAttenuation) {
        if (otherAppearance != nullptr) {
            appearance = (*otherAppearance);
            hasMesh = true;
        }
        lightParams.lightPos = lightPos;
        lightParams.lightDir = lightDir;
        lightParams.lightAttenuation = lightAttenuation;
    }

    const glm::vec3 LightSource::lightPos() const {
        return lightParams.lightPos;
    }

    const glm::vec3 LightSource::lightDir() const {
        return lightParams.lightDir;
    }

    const glm::vec3 LightSource::lightAttenuation() const {
        return lightParams.lightAttenuation;
    }

    const glm::vec3 LightSource::lightColor() const {
        return lightParams.lightColor;
    }

    void LightSource::render(const Shader &program, const Camera &renderCamera) {
        if (hasMesh) appearance.render(program, renderCamera);
    }
}
//
// Created by ekin4 on 26/02/2017.
//

#ifndef IDEK_LIGHTSOURCE_H
#define IDEK_LIGHTSOURCE_H

#include "Mesh.h"

namespace cogl {

    struct LightParameters {
        glm::vec3 lightDir = glm::vec3(0.0f);
        glm::vec3 lightPos = glm::vec3(0.0f);
        glm::vec3 lightAttenuation = glm::vec3(0.0f);
    };

    struct LightBlock {
        glm::vec3 lightPos;
        glm::vec3 lightDir;
        glm::vec3 lightColor;
        glm::vec3 lightAttenuation;
    };

    class LightSource {
    protected:
        bool hasMesh = false;
        Mesh appearance;
        LightBlock lightParams;
    public:
        // Constructors //
        LightSource(const Mesh *appearance = nullptr,
                    const glm::vec3 &lightDir = glm::vec3(0.0f),
                    const glm::vec3 &lightPos = glm::vec3(0.0f),
                    const glm::vec3 &lightAttenuation = glm::vec3(0.0f));

        void render(const Shader &program, const Camera &renderCamera);

        const glm::vec3 lightPos() const;

        const glm::vec3 lightDir() const;

        const glm::vec3 lightAttenuation() const;

        const glm::vec3 lightColor() const;
    };

}
#endif //IDEK_LIGHTSOURCE_H

//
// Created by ekin4 on 29/04/2017.
//

#ifndef CUSTOMOGL_RENDERABLE_H
#define CUSTOMOGL_RENDERABLE_H

#include "../Constants.h"
#include "Shader.h"
#include "Camera.h"

namespace cogl {
    enum RenderTypes {
        Ls = GL_LINES,
        LLoop = GL_LINE_LOOP,
        LStrip = GL_LINE_STRIP,

        Tris = GL_TRIANGLES,
        TriFan = GL_TRIANGLE_FAN,
        TriStrip = GL_TRIANGLE_STRIP,

        Points = GL_POINTS,

        Patches = GL_PATCHES,
    };

    struct alignas(8) Vertex {
        float x, y, z;
        float nx, ny, nz;
        float r, g, b, alpha;
        float u, v;

        friend std::ostream &operator<<(std::ostream &outstream, const Vertex &rhs) {
            outstream << "x: " << rhs.x << ", ";
            outstream << "y: " << rhs.y << ", ";
            outstream << "z: " << rhs.z << " || ";
            outstream << "nx: " << rhs.nx << ", ";
            outstream << "ny: " << rhs.ny << ", ";
            outstream << "nz: " << rhs.nz << " || ";
            outstream << "r: " << rhs.r << ", ";
            outstream << "g: " << rhs.g << ", ";
            outstream << "b: " << rhs.b << ", ";
            outstream << "alpha: " << rhs.alpha << " || ";
            outstream << "u: " << rhs.u << ", ";
            outstream << "v: " << rhs.v;
            return outstream;
        }
    };

    class Renderable {
    public:
        virtual void initialiseVAO() = 0;

        virtual void clearVAO() = 0;

        virtual void render(const Shader &program, const Camera &renderCamera) = 0;
    };
}

#endif //CUSTOMOGL_RENDERABLE_H

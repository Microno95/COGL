//
// Created by ekin4 on 29/04/2017.
//

#ifndef CUSTOMOGL_RENDERABLE_H
#define CUSTOMOGL_RENDERABLE_H

#include "Constants.h"
#include "Shader.h"
#include "Camera.h"

/*
 * This file defines the primitives used in the cogl library.
 *
 * RenderTypes enumerates the various GL_ rendering schemes under shorter names.
 * This is for code brevity rather than clarity though the shorthand names have been
 * made to be as clear as possible.
 *
 * The Vertex is the current vertex data structure that stores positions, normals,
 * vertex colours and uv coordinates.
 *
 * Renderable is a pure virtual class that defines an interface for the necessary functions required
 * to create/delete VAOs and to render objects which take Shader and Camera arguments.
 * */

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

    struct alignas(4) Vertex {
		union {
			struct { float pos[4]; };
			struct { float x, y, z, w; };
			struct { glm::vec4 glm_pos; };
		};
		union {
			struct { float nrm[4]; };
			struct { float nx, ny, nz, nw; };
			struct { glm::vec4 glm_nrm; };
		};
		union {
			struct { float rgba[4]; };
			struct { float r, g, b, a; };
			struct { glm::vec4 glm_rgba; };
		};
		union {
			struct { float uv[4]; };
			struct { float u, v, w, p; };
			struct { glm::vec4 glm_uv; };
		};
		
		Vertex &Vertex::operator=(const Vertex& other) {
			memcpy(this, &other, sizeof(Vertex));
			return *this;
		};

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
            outstream << "a: " << rhs.a << " || ";
            outstream << "u: " << rhs.u << ", ";
            outstream << "v: " << rhs.v;
            return outstream;
        }
    };

    class Renderable {
    public:
        virtual void render(const Shader &program, const Camera &renderCamera, bool update_gpu_data) = 0;
    };
}

#endif //CUSTOMOGL_RENDERABLE_H

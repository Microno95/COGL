//
// Created by ekin4 on 23/02/2017.
//

#ifndef IDEK_MESHES_H
#define IDEK_MESHES_H

#include "Renderable.h"

/*
 * Generic class to store Mesh data.
 *
 * Uses indexed vertices to render with opengl. The vertices and indices are stored in the
 * vertices and indices std::vectors.
 *
 * The mesh retains the rotation, translation and scaling matrices separate in order to allow
 * easier manipulation at the cost of runtime performance.
 *
 * The normal matrix is recalculated whenever a transformation such as a rotation, translation or a scaling is applied.
 * This is to ensure that when the mesh is being rendered the normal matrix is ready to be streamed to the GPU.
 *
 * The MVP (Model-View-Projection) matrix is calculated every frame using the given Camera instance. This allows
 * dynamically redrawing from different views and affords the opportunity to change cameras at will
 * by swapping the given Camera instance.
 *
 * Similarly, the render method also takes a Shader instance that determines the vertex and fragment shading
 * that will be applied to the mesh. This enables changing the rendering scheme.
 *
 * TODO:
 *  - Add ability to use deferred shading, currently this requires having a set of Light Source instances
 *    that the render method needs to accept as an argument. Somewhat tricky.
 *  - Potentially add the ability to remesh at will, this will require an overhaul of the mesh data structure
 *    as the current setup does not allow for variable number of nor remeshing of an existing set of vertices.
 *    Alternatively, this could be done through just recreating the mesh and so may not be necessary.
 *  - Add the ability to load in .stl files as well. This requires distinguishing between ASCII and binary stl
 *    which may be tricky depending on the software that saved the stl in the first place.
 *
 * */

namespace cogl {
    class Mesh : public Renderable {
    private:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        glm::mat4x4 rotMatrix, transMatrix, scaleMatrix, normalMatrix;
        RenderTypes renderType;

    protected:
        bool VAO_initialised = false;
        GLuint VAO, vertexBuffer, indexBuffer;
    public:

        Mesh();

        Mesh(const Mesh &other);

        Mesh(const std::vector<Vertex> &verticesInit);

        Mesh(const std::vector<Vertex> &verticesInit, const std::vector<unsigned int> &indicesInit,
             RenderTypes rType = RenderTypes::Tris);

        //Move Constructor
        Mesh(Mesh &&other);

        // Move Assignment
        Mesh &operator=(Mesh &&other);

        // Copy Assignment
        Mesh &operator=(const Mesh &other);

        // Destructor
        ~Mesh();

        void initialiseVAO() override;

        void clearVAO() override;

        void render(const Shader &program, const Camera &renderCamera) override;

        void rotateMesh(const double angle, const glm::vec3 axisOfRotation);

        void scaleMesh(const double xScale, const double yScale, const double zScale);

        void scaleMesh(const double &scale) { this->scaleMesh(scale, scale, scale); };

        void moveMesh(const glm::vec3 translation);

        void moveMeshTo(const glm::vec3 translation);

        void setRenderType(const RenderTypes rType);

        const std::vector<Vertex> getVertices() const;

        const std::vector<unsigned int> getIndices() const;

        const RenderTypes getRenderType() const;

        const glm::mat4x4 getModelMatrix() const;

        const glm::mat4x4 getNormalMatrix() const;

        const glm::mat4x4 getTransMatrix() const;

        const glm::mat4x4 getRotMatrix() const;

        const glm::mat4x4 getScaleMatrix() const;

        // Default Shapes //
        static const Mesh Cube;
        static const Mesh Icosahedron;
        // -------------- //

        friend std::ostream &operator<<(std::ostream &outstream, const Mesh &rhs) {
            for (auto i = 0; i < rhs.vertices.size(); ++i) {
                std::cout << "Vertex " << i << ":" << std::endl << rhs.vertices[i] << std::endl;
            }
            for (auto i : rhs.indices) std::cout << i << ", ";
            std::cout << std::endl;
            std::cout << glm::to_string(rhs.getModelMatrix()) << std::endl;
            return outstream;
        }

        static Mesh load_from_obj(const std::string filename);
    };

}
#endif //IDEK_MESHES_H

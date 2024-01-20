#ifndef SPHERE_H
#define SPHERE_H

// Standard headers
#include <cmath>
#include <vector>

// GLEW
#include <GL/glew.h>

// GLM
#include <glm/glm.hpp>

// Local headers
#include "constants.h"

/**
 * Sphere class for creating and rendering a 3D sphere in OpenGL.
 * It supports texture mapping and is configurable in terms of segment density.
 */
class Sphere {
public:
    Sphere(unsigned int xSegments, unsigned int ySegments);

    /**
    * Sets the texture ID for the sphere.
    * @param newTextureID The texture ID to be set for the sphere.
    */
    void setTexture(GLuint textureID);

    /**
     * Draws the sphere using the current OpenGL context.
     */
    void draw();

private:
    void init();

    std::vector<glm::vec3> positions; // Vertex positions of the sphere
    std::vector<glm::vec2> uv;        // UV texture coordinates
    std::vector<glm::vec3> normals;   // Normals for lighting calculations
    std::vector<unsigned int> indices; // Indices for indexed drawing of the sphere

    unsigned int xSegments, ySegments; // Segment density of the sphere
    unsigned int VAO, VBO, EBO, UVBO; // OpenGL buffer and array object IDs
    GLuint textureID; // Texture ID for the sphere
};

#endif

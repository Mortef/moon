#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Sphere {
public:
    Sphere(unsigned int xSegments, unsigned int ySegments);
    void draw();
    void setTexture(GLuint textureID);

private:
    void init();
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;
    unsigned int xSegments, ySegments;
    unsigned int VAO, VBO, EBO, UVBO;
    GLuint textureID;
};

#endif

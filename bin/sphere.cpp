#include "sphere.h"

Sphere::Sphere(unsigned int xSegments, unsigned int ySegments)
    : xSegments(xSegments), ySegments(ySegments) {
    init();
}

void Sphere::init() {
    // Generate sphere vertices, texture coordinates, and normals
    for (unsigned int y = 0; y <= ySegments; ++y) {
        for (unsigned int x = 0; x <= xSegments; ++x) {
            float xSegment = static_cast<float>(x) / xSegments;
            float ySegment = static_cast<float>(y) / ySegments;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

            positions.push_back(glm::vec3(xPos, yPos, zPos));
            uv.push_back(glm::vec2(xSegment, ySegment));
            normals.push_back(glm::vec3(xPos, yPos, zPos));
        }
    }

    // Define indices for sphere's triangles
    for (unsigned int y = 0; y < ySegments; ++y) {
        for (unsigned int x = 0; x < xSegments; ++x) {
            indices.push_back((y + 1) * (xSegments + 1) + x);
            indices.push_back(y * (xSegments + 1) + x);
            indices.push_back(y * (xSegments + 1) + x + 1);

            indices.push_back((y + 1) * (xSegments + 1) + x);
            indices.push_back(y * (xSegments + 1) + x + 1);
            indices.push_back((y + 1) * (xSegments + 1) + x + 1);
        }
    }

    // Setting up OpenGL buffers and attributes
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), &positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glGenBuffers(1, &UVBO);
    glBindBuffer(GL_ARRAY_BUFFER, UVBO);
    glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}


void Sphere::setTexture(GLuint newTextureID) {
    textureID = newTextureID;
}

void Sphere::draw() {
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

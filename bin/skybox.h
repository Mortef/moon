#ifndef SKYBOX_H
#define SKYBOX_H

// Standard libraries
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// GLEW
#include <GL/glew.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


/**
 * Skybox class for creating and rendering a skybox in OpenGL.
 * It manages the textures, shaders, and geometry necessary for rendering.
 */
class Skybox {
public:
    Skybox();
    ~Skybox();

    /**
     * Sets the texture ID for the skybox.
     * @param textureID The OpenGL texture ID to be used.
     */
    void setTexture(GLuint textureID);

    /**
     * Renders the skybox using the specified view and projection matrices.
     * @param view The view matrix for rendering.
     * @param projection The projection matrix for rendering.
     */
    void draw(const glm::mat4& view, const glm::mat4& projection);

    /**
     * Loads and compiles the vertex and fragment shaders for the skybox.
     * @param vertexShaderPath Path to the vertex shader file.
     * @param fragmentShaderPath Path to the fragment shader file.
     */
    void loadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

private:
    GLuint VAO, VBO;           // Vertex Array Object and Vertex Buffer Object
    GLuint textureID;          // Texture ID for the skybox
    GLuint shaderProgram;      // Shader program ID

    /**
     * Sets up the geometry for the skybox.
     */
    void setupSkybox();

    /**
     * Compiles a shader from the given file.
     * @param shaderPath Path to the shader file.
     * @param shaderType Type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER).
     * @return The compiled shader's ID.
     */
    GLuint compileShader(const std::string& shaderPath, GLenum shaderType);
};

#endif

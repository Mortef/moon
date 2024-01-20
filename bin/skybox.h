#ifndef SKYBOX_H
#define SKYBOX_H

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Skybox {
public:
    Skybox();
    ~Skybox();


    void setTexture(GLuint textureID);
    void draw(const glm::mat4& view, const glm::mat4& projection);
    void loadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

private:
    GLuint VAO, VBO;
    GLuint textureID;
    GLuint shaderProgram;

    void setupSkybox();
    GLuint compileShader(const std::string& shaderPath, GLenum shaderType);
};

#endif

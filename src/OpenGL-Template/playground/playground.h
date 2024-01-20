#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <GL/glew.h>
#include <glfw3.h>

#include "constants.h"
#include "sphere.h"
#include "texture_loader.h"
#include "mouse_controller.h"
#include "skybox.h"

class Playground {
public:
    Playground();
    ~Playground();
    void init();
    void mainLoop();

private:
    GLFWwindow* window;
    Sphere* moon;
    Skybox* skybox;
    GLuint programID;
    GLuint moonTextureID, skyboxTextureID;
    MouseController mouse_controller;
};

#endif

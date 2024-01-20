#ifndef PLAYGROUND_H
#define PLAYGROUND_H

// Standard headers
#include <iostream>

// GLEW
#include <GL/glew.h>

// GLFW
#include <glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Local headers
#include "constants.h"
#include "sphere.h"
#include "texture_loader.h"
#include "mouse_controller.h"
#include "skybox.h"
#include <common/shader.hpp>

/**
 * Playground class handles the main OpenGL rendering loop and resource management.
 */
class Playground {
public:
    Playground();
    ~Playground();

    /**
     * Initializes the OpenGL context, window, and resources.
     */
    void init();

    /**
     * Runs the main rendering loop.
     */
    void mainLoop();

    /**
     * Static callback function for handling scroll input.
     * @param window Pointer to GLFWwindow.
     * @param xoffset Horizontal scroll offset.
     * @param yoffset Vertical scroll offset.
     */
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

private:
    // Member variables
    GLFWwindow* window;
    Sphere* moon;
    Skybox* skybox;
    GLuint programID;
    GLuint moonTextureID, skyboxTextureID;
    MouseController mouse_controller;
    float moonScale;

    // Helper functions for initialization
    bool initializeGLFW();
    bool initializeGLEW();
    bool createWindow();
    void configureOpenGL();
    void loadResources();
    void setCallbacks();

    // Helper functions for mainLoop
    glm::vec3 calculateCameraPosition();
    void renderScene(const glm::mat4& View, const glm::mat4& Projection);

    // Helper function for scroll_callback
    void adjustMoonScale(double yoffset);
};

#endif

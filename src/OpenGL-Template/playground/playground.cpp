#include "playground.h"
#include <GL/glew.h>
#include <glfw3.h>
#include <iostream>
#include <common/shader.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Playground::Playground() : moon(nullptr), window(nullptr), programID(0), moonTextureID(0) {}

void Playground::init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Playground", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    glEnable(GL_DEPTH_TEST);

    programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

    moon = new Sphere(64, 64);

    moonTextureID = loadTexture("moon_texture.png");
    moon->setTexture(moonTextureID);

    glfwSetCursorPosCallback(window, MouseController::mouse_callback);
}

void Playground::mainLoop() {
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        GLuint moonTextureUniform = glGetUniformLocation(programID, "moonTexture");
        glUniform1i(moonTextureUniform, 0);

        glm::mat4 Model = glm::mat4(1.0f);
        Model = glm::rotate(Model, glm::radians(mouse_controller.get_moon_rotation_x()), glm::vec3(1, 0, 0));
        Model = glm::rotate(Model, glm::radians(mouse_controller.get_moon_rotation_y()), glm::vec3(0, 1, 0));

        glm::vec3 cameraPos = glm::vec3(4, 3, -3);
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 direction = glm::normalize(-cameraPos);
        glm::vec3 right = glm::normalize(glm::cross(up, direction));

        cameraPos = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(mouse_controller.get_camera_rotation_y()), up)) * cameraPos;
        cameraPos = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(mouse_controller.get_camera_rotation_x()), right)) * cameraPos;

        glm::mat4 View = glm::lookAt(cameraPos, glm::vec3(0, 0, 0), up);

        glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 0.1f, 100.0f);

        glm::mat4 MVP = Projection * View * Model;

        GLuint MatrixID = glGetUniformLocation(programID, "MVP");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        glBindTexture(GL_TEXTURE_2D, moonTextureID);
        moon->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (!glfwWindowShouldClose(window));
}

Playground::~Playground() {
    if (moon) {
        delete moon;
    }
    glfwDestroyWindow(window);
    glfwTerminate();
}

int main() {
    Playground app;
    app.init();
    app.mainLoop();
    return 0;
}


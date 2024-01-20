#include "playground.h"
#include <GL/glew.h>
#include <glfw3.h>
#include <iostream>
#include <common/shader.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Playground::Playground() : moon(nullptr), skybox(nullptr), window(nullptr), programID(0), moonTextureID(0), skyboxTextureID(0), moonScale(1.0f) {}

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
    moonTextureID = loadTexture("moon_texture.jpg");
    moon->setTexture(moonTextureID);

    skybox = new Skybox();
    skybox->loadShaders("SkyboxVertexShader.vertexshader", "SkyboxFragmentShader.fragmentshader");
    skyboxTextureID = loadTexture("milky_texture.jpg");
    skybox->setTexture(skyboxTextureID);

    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, MouseController::mouse_callback);
    glfwSetScrollCallback(window, Playground::scroll_callback);
}

void Playground::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Playground* playground = static_cast<Playground*>(glfwGetWindowUserPointer(window));
    if (playground) {
        playground->moonScale += static_cast<float>(yoffset) * 0.05f;
        playground->moonScale = std::max(0.1f, playground->moonScale);
    }
}


void Playground::mainLoop() {
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float distanceFromMoon = 5.0f;

        glm::vec3 cameraPos;
        cameraPos.x = distanceFromMoon * cos(glm::radians(mouse_controller.get_camera_yaw())) * cos(glm::radians(mouse_controller.get_camera_pitch()));
        cameraPos.y = distanceFromMoon * sin(glm::radians(mouse_controller.get_camera_pitch()));
        cameraPos.z = distanceFromMoon * sin(glm::radians(mouse_controller.get_camera_yaw())) * cos(glm::radians(mouse_controller.get_camera_pitch()));

        glm::vec3 moonPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::mat4 View = glm::lookAt(cameraPos, moonPosition, up);

        glm::mat4 Projection = glm::perspective(glm::radians(45.0f), static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT), 0.1f, 100.0f);


        glDepthFunc(GL_LEQUAL);
        skybox->draw(View, Projection);
        glDepthFunc(GL_LESS);

        glUseProgram(programID);
        GLuint moonTextureUniform = glGetUniformLocation(programID, "moonTexture");
        glUniform1i(moonTextureUniform, 0);

        glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(moonScale));
        Model = glm::rotate(Model, glm::radians(mouse_controller.get_moon_rotation_x()), glm::vec3(1, 0, 0));
        Model = glm::rotate(Model, glm::radians(mouse_controller.get_moon_rotation_y()), glm::vec3(0, 1, 0));

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


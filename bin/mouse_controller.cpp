#include "mouse_controller.h"
#include <iostream>

float MouseController::moon_rotation_x = 0.0f;
float MouseController::moon_rotation_y = 0.0f;
float MouseController::camera_rotation_x = 0.0f;
float MouseController::camera_rotation_y = 0.0f;
double MouseController::last_mouse_pos_x = 0.0;
double MouseController::last_mouse_pos_y = 0.0;
bool MouseController::first_mouse = true;

MouseController::MouseController() {}

void MouseController::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (first_mouse) {
        last_mouse_pos_x = xpos;
        last_mouse_pos_y = ypos;
        first_mouse = false;
    }

    double xoffset = xpos - last_mouse_pos_x;
    double yoffset = ypos - last_mouse_pos_y;
    last_mouse_pos_x = xpos;
    last_mouse_pos_y = ypos;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        moon_rotation_x += static_cast<float>(yoffset);
        moon_rotation_y += static_cast<float>(xoffset);
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        camera_rotation_x += static_cast<float>(yoffset);
        camera_rotation_y += static_cast<float>(xoffset);
    }
}

float MouseController::get_moon_rotation_x() const { return moon_rotation_x; }
float MouseController::get_moon_rotation_y() const { return moon_rotation_y; }
float MouseController::get_camera_rotation_x() const { return camera_rotation_x; }
float MouseController::get_camera_rotation_y() const { return camera_rotation_y; }

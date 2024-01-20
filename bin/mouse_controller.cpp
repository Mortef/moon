#include "mouse_controller.h"

// Static member variables initialization
float MouseController::moon_rotation_x = 0.0f;
float MouseController::moon_rotation_y = 0.0f;
float MouseController::camera_yaw = -90.0f;
float MouseController::camera_pitch = 0.0f;
double MouseController::last_mouse_pos_x = 0.0;
double MouseController::last_mouse_pos_y = 0.0;
bool MouseController::first_mouse = true;

MouseController::MouseController() {}

// Handles mouse input for camera and moon rotation.
void MouseController::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (first_mouse) {
        initializeMousePosition(xpos, ypos);
    }

    double xoffset, yoffset;
    calculateOffset(xpos, ypos, xoffset, yoffset);

    updateAngles(window, xoffset, yoffset);
}

void MouseController::initializeMousePosition(double xpos, double ypos) {
    last_mouse_pos_x = xpos;
    last_mouse_pos_y = ypos;
    first_mouse = false;
}

void MouseController::calculateOffset(double xpos, double ypos, double& xoffset, double& yoffset) {
    xoffset = (xpos - last_mouse_pos_x) * MOUSE_SENSITIVITY;
    yoffset = (last_mouse_pos_y - ypos) * MOUSE_SENSITIVITY;
    last_mouse_pos_x = xpos;
    last_mouse_pos_y = ypos;
}

// Custom clamp function
float MouseController::clamp(float value, float min, float max) {
    return (value < min) ? min : (value > max) ? max : value;
}

void MouseController::updateAngles(GLFWwindow* window, double xoffset, double yoffset) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        // Update camera yaw and pitch
        camera_yaw += static_cast<float>(xoffset);
        camera_pitch = clamp(camera_pitch + static_cast<float>(yoffset), -PITCH_LIMIT, PITCH_LIMIT);
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        // Update moon rotation
        moon_rotation_x += static_cast<float>(yoffset);
        moon_rotation_y += static_cast<float>(xoffset);
    }
}

// Getters for rotation angles and camera angles
float MouseController::get_moon_rotation_x() const { return moon_rotation_x; }
float MouseController::get_moon_rotation_y() const { return moon_rotation_y; }
float MouseController::get_camera_yaw() { return camera_yaw; }
float MouseController::get_camera_pitch() { return camera_pitch; }

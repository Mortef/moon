#ifndef MOUSE_CONTROLLER_H
#define MOUSE_CONTROLLER_H

// Standard headers
#include <iostream>
#include <cmath>

// GLFW
#include <glfw3.h>

// Local headers
#include "constants.h"

/**
 * MouseController handles mouse input for controlling camera angles and moon rotation in OpenGL.
 */
class MouseController {
public:
    /**
     * Constructor for MouseController.
     */
    MouseController();

    /**
     * Static callback function for handling mouse movement input.
     * @param window GLFW window.
     * @param xpos Current mouse x position.
     * @param ypos Current mouse y position.
     */
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    // Getters for rotation and camera angles
    float get_moon_rotation_x() const;
    float get_moon_rotation_y() const;
    static float get_camera_yaw();
    static float get_camera_pitch();

    // Custom clamp function
    static float clamp(float value, float min, float max);

private:
    // Member variables for tracking mouse positions and rotations
    static float moon_rotation_x, moon_rotation_y; // Moon rotation angles
    static float camera_yaw, camera_pitch;         // Camera orientation angles
    static double last_mouse_pos_x, last_mouse_pos_y; // Last recorded mouse positions
    static bool first_mouse;                        // Flag for the first mouse movement

    /**
    * Initializes the mouse position variables.
    * @param xpos Current mouse x position.
    * @param ypos Current mouse y position.
    */
    static void initializeMousePosition(double xpos, double ypos);

    /**
    * Calculates the offset of mouse movement.
    * @param xpos Current mouse x position.
    * @param ypos Current mouse y position.
    * @param xoffset Calculated x offset.
    * @param yoffset Calculated y offset.
    */
    static void calculateOffset(double xpos, double ypos, double& xoffset, double& yoffset);

    /**
    * Updates camera or moon angles based on mouse button state.
    * @param window GLFW window.
    * @param xoffset X offset of mouse movement.
    * @param yoffset Y offset of mouse movement.
    */
    static void updateAngles(GLFWwindow* window, double xoffset, double yoffset);
};

#endif

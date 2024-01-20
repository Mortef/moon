#ifndef MOUSE_CONTROLLER_H
#define MOUSE_CONTROLLER_H

#include <glfw3.h>

class MouseController {
public:
    MouseController();

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    float get_moon_rotation_x() const;
    float get_moon_rotation_y() const;
    float get_camera_rotation_x() const;
    float get_camera_rotation_y() const;

private:
    static float moon_rotation_x, moon_rotation_y;
    static float camera_rotation_x, camera_rotation_y;
    static double last_mouse_pos_x, last_mouse_pos_y;
    static bool first_mouse;
};

#endif

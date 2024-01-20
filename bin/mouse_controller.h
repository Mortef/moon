#ifndef MOUSE_CONTROLLER_H
#define MOUSE_CONTROLLER_H

#include <glfw3.h>

class MouseController {
public:
    MouseController();

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    float get_moon_rotation_x() const;
    float get_moon_rotation_y() const;
    static float get_camera_yaw();
    static float get_camera_pitch();

private:
    static float moon_rotation_x, moon_rotation_y;
    static float camera_yaw, camera_pitch;
    static double last_mouse_pos_x, last_mouse_pos_y;
    static bool first_mouse;
};

#endif

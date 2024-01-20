#include "playground.h"

Playground::Playground() : moon(nullptr), skybox(nullptr), window(nullptr), programID(0), moonTextureID(0), skyboxTextureID(0), moonScale(1.0f) {}

// Initialize GLFW and set window hints for OpenGL version and profile
bool Playground::initializeGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    // Configure GLFW for OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return true;
}

// Initialize GLEW to manage OpenGL function pointers
bool Playground::initializeGLEW() {
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return false;
    }
    return true;
}

bool Playground::createWindow() {
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Playground", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    return true;
}

void Playground::configureOpenGL() {
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);
}

void Playground::loadResources() {
    programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

    moon = new Sphere(MOON_SEGMENTS, MOON_SEGMENTS);
    moonTextureID = loadTexture("moon_texture.jpg");
    moon->setTexture(moonTextureID);

    skybox = new Skybox();
    skybox->loadShaders("SkyboxVertexShader.vertexshader", "SkyboxFragmentShader.fragmentshader");
    skyboxTextureID = loadTexture("milky_texture.jpg");
    skybox->setTexture(skyboxTextureID);
}

// Handle scroll input to adjust the scale of an object in the scene
void Playground::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Playground* playground = static_cast<Playground*>(glfwGetWindowUserPointer(window));
    if (playground) {
        playground->adjustMoonScale(yoffset);
    }
}

// Adjust the scale of the moon based on scroll input
void Playground::adjustMoonScale(double yoffset) {
    moonScale += static_cast<float>(yoffset) * SCROLLING_FACTOR;
    moonScale = std::max(MOON_MIN_SCALE, moonScale); // Ensure the scale stays above a minimum value
}


void Playground::setCallbacks() {
    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, MouseController::mouse_callback);
    glfwSetScrollCallback(window, Playground::scroll_callback);
}

void Playground::init() {
    if (!initializeGLFW() || !createWindow() || !initializeGLEW()) {
        return;
    }
    configureOpenGL(); // Set up viewport and enable depth test
    loadResources();   // Load shaders, textures, and other resources
    setCallbacks();    // Set GLFW callbacks for user interaction
}

// Calculate the position of the camera based on mouse input
glm::vec3 Playground::calculateCameraPosition() {
    glm::vec3 cameraPos;
    cameraPos.x = CAMERA_DISTANCE * cos(glm::radians(mouse_controller.get_camera_yaw())) * cos(glm::radians(mouse_controller.get_camera_pitch()));
    cameraPos.y = CAMERA_DISTANCE * sin(glm::radians(mouse_controller.get_camera_pitch()));
    cameraPos.z = CAMERA_DISTANCE * sin(glm::radians(mouse_controller.get_camera_yaw())) * cos(glm::radians(mouse_controller.get_camera_pitch()));
    return cameraPos;
}

// Render the skybox and other objects in the scene
void Playground::renderScene(const glm::mat4& View, const glm::mat4& Projection) {
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
}

// Main rendering loop
void Playground::mainLoop() {
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers
        
        glm::vec3 cameraPos = calculateCameraPosition(); // Update camera position
        glm::vec3 moonPosition = glm::vec3(0.0f, 0.0f, 0.0f); // Compute View matrix
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // Compute Projection matrix
        glm::mat4 View = glm::lookAt(cameraPos, moonPosition, up); // View matrix calculation
        glm::mat4 Projection = glm::perspective(glm::radians(PROJECTION_FOV), static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT), PROJECTION_NEAR_PLANE, PROJECTION_FAR_PLANE); // Projection matrix calculation

        renderScene(View, Projection);  // Render the scene

        glfwSwapBuffers(window); // Swap buffers and poll for IO events
        glfwPollEvents();
    } while (!glfwWindowShouldClose(window)); // Check if the window was instructed to close
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


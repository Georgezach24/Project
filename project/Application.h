#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "PatternRenderer.h"
#include "GuiController.h"
#include "PatternFramebuffer.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"

class Application {
public:
    void run();

    // 🔓 Public για πρόσβαση από mouse_callback
    float lastX = 640.0f;
    float lastY = 360.0f;
    bool firstMouse = true;
    Camera camera = Camera(
        glm::vec3(0.0f, 1.0f, 5.0f),   // position
        glm::vec3(0.0f, 1.0f, 0.0f),   // up
        -90.0f, 0.0f                   // yaw, pitch
    );

private:
    void init();
    void loop();
    void cleanup();
    void renderSceneWithLighting();
    void processInput();

    GLFWwindow* window = nullptr;

    std::unique_ptr<PatternRenderer> renderer;
    std::unique_ptr<GuiController> gui;
    std::unique_ptr<PatternFramebuffer> framebuffer;
    std::unique_ptr<Shader> lightingShader;
    std::unique_ptr<Model> model;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
};

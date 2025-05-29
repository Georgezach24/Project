#pragma once
#include <memory>
#include "Shader.h"
#include "PatternRenderer.h"
#include "GuiController.h"
#include <glfw3.h> 

class Application {
public:
    void run();

private:
    void init();
    void loop();
    void cleanup();

    GLFWwindow* window = nullptr;
    std::unique_ptr<PatternRenderer> renderer;
    std::unique_ptr<GuiController> gui;
};
#pragma once
#include <GLFW/glfw3.h>
#include <memory>
#include "PatternRenderer.h"
#include "GuiController.h"

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
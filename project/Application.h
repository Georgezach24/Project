#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "PatternRenderer.h"
#include "GuiController.h"
#include "PatternFramebuffer.h"
#include "Shader.h"
#include "Model.h"

class Application {
public:
    void run();

private:
    void init();
    void loop();
    void cleanup();

    void initScreenQuad();
    void renderSceneWithLighting();

    GLFWwindow* window = nullptr;

    std::unique_ptr<PatternRenderer> renderer;
    std::unique_ptr<GuiController> gui;
    std::unique_ptr<PatternFramebuffer> framebuffer;
    std::unique_ptr<Shader> lightingShader;
    std::unique_ptr<Model> model;

    unsigned int screenQuadVAO = 0, screenQuadVBO = 0;
};

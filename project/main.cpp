#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "PatternRenderer.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// ==== Callbacks ====
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);

// ==== Settings ====
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// ==== Camera ====
Camera camera(glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.f, 0.f);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool showGUI = false;

// Timing
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

int main() {

    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "3D Bunny Scene", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int w, int h) { glViewport(0, 0, w, h); });
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // Shaders
    Shader shader("textured_lighting.vert", "textured_lighting.frag");

    // Models and renderer
    PatternRenderer renderer;
    Model bunny("bunny_lp.obj");
    Model ground("plane.obj");

    glm::vec3 lightPos(5.0f, 5.0f, 5.0f);

    // === ImGui Setup ===
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // === GUI parameters ===
    int patternType = 0;
    float scale = 5.0f;
    float rotation = 0.0f;
    float color[3] = {1.0f, 1.0f, 1.0f};

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        // === Update pattern texture ===
        renderer.setPatternType(patternType);
        renderer.setScale(scale);
        renderer.setRotation(rotation);
        renderer.setColor(color[0], color[1], color[2]);
        renderer.render();

        // === Draw Scene ===
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(SCR_WIDTH) / SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        shader.setVec3("lightPos", lightPos);
        shader.setVec3("viewPos", camera.Position);

        // draw ground WITHOUT pattern
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0); // unbind pattern
        shader.setInt("patternTexture", 0);

        glm::mat4 groundModel = glm::mat4(1.0f);
        groundModel = glm::translate(groundModel, glm::vec3(0.0f, -1.0f, 0.0f));
        groundModel = glm::scale(groundModel, glm::vec3(10.0f, 1.0f, 10.0f));
        shader.setMat4("model", groundModel);
        shader.setBool("useTexture", false);
        ground.Draw();

        // bind pattern texture before bunny
        glBindTexture(GL_TEXTURE_2D, renderer.getTexture());

        // draw bunny
        glm::mat4 bunnyModelMat = glm::mat4(1.0f);
        bunnyModelMat = glm::translate(bunnyModelMat, glm::vec3(0.0f, 0.0f, 0.0f));
        bunnyModelMat = glm::scale(bunnyModelMat, glm::vec3(1.0f));
        shader.setMat4("model", bunnyModelMat);
        shader.setBool("useTexture", true);
        bunny.Draw();

        // === ImGui Interface ===
        if (showGUI) {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Pattern Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
            const char* items[] = {"Stripes", "Circles", "Triangles", "Hexagons"};

            ImGui::Combo("Pattern", &patternType, items, IM_ARRAYSIZE(items));
            ImGui::SliderFloat("Scale", &scale, 1.0f, 20.0f);
            ImGui::SliderFloat("Rotation", &rotation, 0.0f, 6.28f);
            ImGui::ColorEdit3("Color", color);
            ImGui::End();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // === Cleanup ===
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    if (!showGUI) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);

        // Clamp camera height above ground
        if (camera.Position.y < 0.1f)
            camera.Position.y = 0.1f;
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (showGUI) return;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void key_callback(GLFWwindow* window, int key, int, int action, int) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        showGUI = !showGUI;
        if (showGUI) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            firstMouse = true;
        }
    }
}

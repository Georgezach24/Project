#include "GuiController.h"
#include <imgui.h>
#include <cmath> // for M_PI if needed

GuiController::GuiController(PatternRenderer& renderer) 
    : renderer(renderer), currentScale(5.0f), currentRotation(0.0f) {
    renderer.setScale(currentScale);
    renderer.setRotation(currentRotation * 3.14159265f / 180.0f);
}

void GuiController::draw() {
    ImGui::Begin("Pattern Selector");

    const char* patterns[] = {"Stripes", "Circles", "Triangles", "Hexagons"};
    if (ImGui::Combo("Pattern", &selectedPattern, patterns, IM_ARRAYSIZE(patterns))) {
        renderer.setPatternType(selectedPattern);
    }

    if (ImGui::SliderFloat("Scale", &currentScale, 1.0f, 30.0f)) {
        renderer.setScale(currentScale);
    }

    if (ImGui::SliderFloat("Rotation (°)", &currentRotation, 0.0f, 360.0f)) {
        float radians = currentRotation * 3.14159265f / 180.0f;
        renderer.setRotation(radians);
    }

    ImGui::End();
}

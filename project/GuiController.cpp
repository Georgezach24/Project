#include "GuiController.h"
#include <imgui.h>

GuiController::GuiController(PatternRenderer& renderer) : renderer(renderer), currentScale(5.0f) {
    renderer.setScale(currentScale);
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

    ImGui::End();
}

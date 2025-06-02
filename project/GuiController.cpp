#include "GuiController.h"
#include <imgui.h>

GuiController::GuiController(PatternRenderer& renderer) : renderer(renderer) {}

void GuiController::draw() {
    ImGui::Begin("Pattern Selector");
    const char* patterns[] = {"Stripes", "Circles", "Triangles", "Hexagons"};
    if (ImGui::Combo("Pattern", &selectedPattern, patterns, IM_ARRAYSIZE(patterns))) {
        renderer.setPatternType(selectedPattern);
    }
    ImGui::End();
}
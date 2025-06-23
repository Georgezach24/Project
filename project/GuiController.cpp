#include "GuiController.h"
#include <imgui.h>

GuiController::GuiController(PatternRenderer& renderer) : renderer(renderer) {
    renderer.setPatternType(selectedPattern);
    renderer.setScale(currentScale);
    renderer.setRotation(currentRotation);
    renderer.setColor(color[0], color[1], color[2]);
}

void GuiController::draw() {
    ImGui::Begin("Pattern Controls");

    const char* patterns[] = { "Stripes", "Circles", "Triangles", "Hexagons" };
    if (ImGui::Combo("Pattern", &selectedPattern, patterns, IM_ARRAYSIZE(patterns)))
        renderer.setPatternType(selectedPattern);

    if (ImGui::SliderFloat("Scale", &currentScale, 1.0f, 20.0f))
        renderer.setScale(currentScale);

    if (ImGui::SliderFloat("Rotation (rad)", &currentRotation, 0.0f, 6.28f))
        renderer.setRotation(currentRotation);

    if (ImGui::ColorEdit3("Color", color))
        renderer.setColor(color[0], color[1], color[2]);

    ImGui::End();
}

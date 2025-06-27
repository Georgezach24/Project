#include "GuiController.h"
#include <imgui.h>

GuiController::GuiController(PatternRenderer& renderer) : renderer(renderer) {
    renderer.setPatternType(selectedPattern);
    renderer.setScale(currentScale);
    renderer.setRotation(currentRotation);
    renderer.setStripeWidth(stripeWidth);
    renderer.setCircleRadius(circleRadius);
    renderer.setTriangleSize(triangleSize);
    renderer.setHexSize(hexSize);
    renderer.setColor(color[0], color[1], color[2]);
}

void GuiController::draw() {
    ImGui::Begin("Pattern Controls");

    const char* patterns[] = { "Stripes", "Circles", "Triangles", "Hexagons" };
    if (ImGui::Combo("Pattern", &selectedPattern, patterns, IM_ARRAYSIZE(patterns)))
        renderer.setPatternType(selectedPattern);

    if (ImGui::SliderFloat("Scale", &currentScale, 1.0f, 20.0f))
        renderer.setScale(currentScale);

    if (ImGui::SliderFloat("Rotation", &currentRotation, 0.0f, 6.28f))
        renderer.setRotation(currentRotation);

    if (ImGui::SliderFloat("Stripe Width", &stripeWidth, 0.01f, 1.0f))
        renderer.setStripeWidth(stripeWidth);

    if (ImGui::SliderFloat("Circle Radius", &circleRadius, 0.01f, 0.5f))
        renderer.setCircleRadius(circleRadius);

    if (ImGui::SliderFloat("Triangle Size", &triangleSize, 0.01f, 1.0f))
        renderer.setTriangleSize(triangleSize);

    if (ImGui::SliderFloat("Hexagon Size", &hexSize, 0.01f, 1.0f))
        renderer.setHexSize(hexSize);

    if (ImGui::ColorEdit3("Color", color))
        renderer.setColor(color[0], color[1], color[2]);

    ImGui::End();
}

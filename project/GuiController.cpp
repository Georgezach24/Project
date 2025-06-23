#include "GuiController.h"
#include <imgui.h>
#include <cmath> 

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
    
    if (selectedPattern == 0) {
        if (ImGui::SliderFloat("Stripe Width", &stripeWidth, 0.01f, 1.0f)) {
            renderer.setStripeWidth(stripeWidth);
        }
    } else if (selectedPattern == 1) {
        if (ImGui::SliderFloat("Circle Radius", &circleRadius, 0.01f, 0.5f)) {
            renderer.setCircleRadius(circleRadius);
        }
    } else if (selectedPattern == 2) {
        if (ImGui::SliderFloat("Triangle Size", &triangleSize, 0.2f, 2.0f)) {
            renderer.setTriangleSize(triangleSize);
        }
    } else if (selectedPattern == 3) {
        if (ImGui::SliderFloat("Hexagon Size", &hexSize, 1.0f,3.0f)) {
            renderer.setHexSize(hexSize);
        }
    }

    // Color picker
    if (ImGui::ColorEdit3("Pattern Color", color)) {
        renderer.setColor(color[0], color[1], color[2]);
    }

    ImGui::End();
}

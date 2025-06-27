#pragma once
#include "PatternRenderer.h"

class GuiController {
public:
    GuiController(PatternRenderer& renderer);
    void draw();

private:
    PatternRenderer& renderer;
    int selectedPattern = 0;
    float currentScale = 5.0f;
    float currentRotation = 0.0f;
    float stripeWidth = 0.5f;
    float circleRadius = 0.25f;
    float triangleSize = 0.5f;
    float hexSize = 0.5f;
    float color[3] = {1.0f, 1.0f, 1.0f};
};

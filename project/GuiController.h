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

    // Pattern-specific GUI state
    float stripeWidth = 0.5f;
    float circleRadius = 0.25f;
    float triangleSize = 1.0f;
    float hexSize = 5.0f;
};

#pragma once
#include "Shader.h"

class PatternRenderer {
public:
    PatternRenderer();
    void render();
    void setPatternType(int type);
    void setScale(float s);
    void setRotation(float angle);

    // New pattern-specific setters
    void setStripeWidth(float w);
    void setCircleRadius(float r);
    void setTriangleSize(float s);
    void setHexSize(float s);

private:
    Shader shader;
    unsigned int quadVAO = 0, quadVBO = 0;
    int patternType = 0;
    float scale = 5.0f;
    float rotation = 0.0f;

    // Pattern-specific GUI state
    float stripeWidth = 0.5f;
    float circleRadius = 0.25f;
    float triangleSize = 1.0f;
    float hexSize = 5.0f;

    void initQuad();
};

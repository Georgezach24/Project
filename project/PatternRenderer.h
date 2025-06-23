#pragma once
#include "Shader.h"

class PatternRenderer {
public:
    PatternRenderer();
    void render();
    void setPatternType(int type);
    void setScale(float s);
    void setRotation(float angle);

    void setStripeWidth(float w);
    void setCircleRadius(float r);
    void setTriangleSize(float s);
    void setHexSize(float s);
    void setColor(float r, float g, float b);

    unsigned int getPatternTexture() const;

private:
    Shader shader;
    unsigned int quadVAO = 0, quadVBO = 0;
    unsigned int fbo = 0, patternTexture = 0, rbo = 0;

    int patternType = 0;
    float scale = 5.0f;
    float rotation = 0.0f;
    float stripeWidth = 0.5f;
    float circleRadius = 0.25f;
    float triangleSize = 1.0f;
    float hexSize = 1.0f;
    float color[3] = {1.0f, 1.0f, 1.0f};

    void initQuad();
    void initFramebuffer();
};

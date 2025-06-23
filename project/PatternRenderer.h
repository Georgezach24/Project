#pragma once
#include "Shader.h"

class PatternRenderer {
public:
    PatternRenderer();
    void render();

    void setPatternType(int type);
    void setScale(float s);
    void setRotation(float angle);
    void setColor(float r, float g, float b);

    GLuint getPatternTexture() const;

private:
    Shader shader;
    GLuint quadVAO = 0, quadVBO = 0;
    GLuint fbo = 0, texture = 0, rbo = 0;

    int patternType = 0;
    float scale = 5.0f;
    float rotation = 0.0f;
    float color[3] = {1.0f, 1.0f, 1.0f};

    void initQuad();
    void initFramebuffer();
};

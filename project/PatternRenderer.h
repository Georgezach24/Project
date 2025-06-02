#pragma once
#include "Shader.h"

class PatternRenderer {
public:
    PatternRenderer();
    void render();
    void setPatternType(int type);
    void setScale(float s);
    void setRotation(float angle);


private:
    Shader shader;
    unsigned int quadVAO = 0, quadVBO = 0;
    int patternType = 0;
    float scale = 5.0f;
    float rotation = 0.0f;
    void initQuad();
};

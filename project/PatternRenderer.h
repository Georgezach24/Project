#pragma once
#include "Shader.h"

class PatternRenderer {
public:
    PatternRenderer();
    void render();
    void setPatternType(int type);

private:
    Shader shader;
    unsigned int quadVAO = 0, quadVBO = 0;
    int patternType = 0;
    void initQuad();
};

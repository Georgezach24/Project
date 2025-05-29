#include "PatternRenderer.h"
#include <glad.h>

static const char* vertexShaderSrc = R"(
#version 330 core
layout(location = 0) in vec2 aPos;
out vec2 TexCoords;
void main() {
    TexCoords = aPos * 0.5 + 0.5;
    gl_Position = vec4(aPos, 0.0, 1.0);
})";

static const char* fragmentShaderSrc = R"(
#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
uniform int uPatternType;

float stripes(vec2 uv) {
    return step(0.5, fract(uv.x * 10.0));
}

float circles(vec2 uv) {
    vec2 grid = fract(uv * 5.0);
    float d = length(grid - 0.5);
    return step(d, 0.25);
}

void main() {
    float pattern = 0.0;
    if (uPatternType == 0) pattern = stripes(TexCoords);
    else if (uPatternType == 1) pattern = circles(TexCoords);
    FragColor = vec4(vec3(pattern), 1.0);
})";

PatternRenderer::PatternRenderer() : shader(vertexShaderSrc, fragmentShaderSrc) {
    initQuad();
}

void PatternRenderer::initQuad() {
    float quad[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f,
    };
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void PatternRenderer::render() {
    shader.use();
    shader.setInt("uPatternType", patternType);
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void PatternRenderer::setPatternType(int type) {
    patternType = type;
}
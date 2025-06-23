#include "PatternRenderer.h"
#include <glad/glad.h>

static const char* vertexShaderSrc = R"(
#version 330 core
layout(location = 0) in vec2 aPos;
out vec2 TexCoords;
void main() {
    TexCoords = aPos * 0.5 + 0.5;
    gl_Position = vec4(aPos, 0.0, 1.0);
}
)";

static const char* fragmentShaderSrc = R"(
#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform int uPatternType;
uniform float uScale;
uniform float uRotation;
uniform float uStripeWidth;
uniform float uCircleRadius;
uniform float uTriangleSize;
uniform float uHexSize;
uniform vec3 uColor;

vec2 rotate(vec2 uv, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    uv -= 0.5;
    uv = mat2(c, -s, s, c) * uv;
    uv += 0.5;
    return uv;
}

float stripes(vec2 uv) {
    return step(uStripeWidth, fract(uv.x * uScale));
}

float circles(vec2 uv) {
    vec2 grid = fract(uv * uScale);
    float d = length(grid - 0.5);
    return step(d, uCircleRadius);
}

float triangles(vec2 uv) {
    uv *= uScale;
    uv.y += floor(uv.x) * 0.5;
    vec2 tri = fract(uv);
    return step(tri.x, 1.0 - tri.y * uTriangleSize);
}

float hexagons(vec2 uv) {
    float s = sqrt(3.0);
    uv *= uScale;
    uv.x *= 2.0 / s;
    uv.y += mod(floor(uv.x), 2.0) * 0.5;

    vec2 a = fract(uv) - 0.5;
    vec2 b = abs(a);
    float d = max(b.x * 1.5 + b.y, b.y * 2.0);

    return step(d, uHexSize * 0.25);
}

void main() {
    vec2 uv = rotate(TexCoords, uRotation);
    float pattern = 0.0;

    if (uPatternType == 0)
        pattern = stripes(uv);
    else if (uPatternType == 1)
        pattern = circles(uv);
    else if (uPatternType == 2)
        pattern = triangles(uv);
    else if (uPatternType == 3)
        pattern = hexagons(uv);

    FragColor = vec4(pattern * uColor, 1.0);
}
)";

PatternRenderer::PatternRenderer() : shader(vertexShaderSrc, fragmentShaderSrc), scale(5.0f), rotation(0.0f) {
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
    shader.setFloat("uScale", scale);
    shader.setFloat("uRotation", rotation);
    shader.setFloat("uStripeWidth", stripeWidth);
    shader.setFloat("uCircleRadius", circleRadius);
    shader.setFloat("uTriangleSize", triangleSize);
    shader.setFloat("uHexSize", hexSize);
    shader.setVec3("uColor", color[0], color[1], color[2]);
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void PatternRenderer::setPatternType(int type) {
    patternType = type;
}

void PatternRenderer::setScale(float s) {
    scale = s;
}

void PatternRenderer::setRotation(float angle) {
    rotation = angle;
}

void PatternRenderer::setStripeWidth(float w) { 
    stripeWidth = w; 
}

void PatternRenderer::setCircleRadius(float r) { 
    circleRadius = r; 
}

void PatternRenderer::setTriangleSize(float s) { 
    triangleSize = s; 
}

void PatternRenderer::setHexSize(float s) { 
    hexSize = s; 
}

void PatternRenderer::setColor(float r, float g, float b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}
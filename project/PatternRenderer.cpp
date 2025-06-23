#include "PatternRenderer.h"
#include <glad/glad.h>
#include <iostream>

static const char* vertexShaderSrc = R"(
#version 330 core
layout(location = 0) in vec2 aPos;
out vec2 TexCoords;
void main() {
    TexCoords = (aPos + 1.0) / 2.0;
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
uniform vec3 uColor;

mat2 rotate(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    return mat2(c, -s, s, c);
}

void main() {
    vec2 uv = TexCoords * uScale - 0.5 * uScale;
    uv = rotate(uRotation) * uv;

    float val = 0.0;

    if (uPatternType == 0) {
        val = step(0.5, mod(uv.x, 1.0));
    } else if (uPatternType == 1) {
        val = step(length(fract(uv) - 0.5), 0.25);
    } else if (uPatternType == 2) {
        val = step(0.5, mod(uv.x + uv.y, 1.0));
    } else if (uPatternType == 3) {
        vec2 hex = vec2(1.0, sqrt(3.0));
        vec2 grid = mod(uv, hex) - 0.5 * hex;
        val = step(length(grid), 0.5);
    }

    FragColor = vec4(uColor * val, 1.0);
}
)";

PatternRenderer::PatternRenderer() : shader(vertexShaderSrc, fragmentShaderSrc) {
    initQuad();
    initFramebuffer();
}

void PatternRenderer::initQuad() {
    float quad[] = {-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f};
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void PatternRenderer::initFramebuffer() {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1024, 1024);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "PatternRenderer framebuffer not complete!\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PatternRenderer::render() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, 1024, 1024);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    shader.setInt("uPatternType", patternType);
    shader.setFloat("uScale", scale);
    shader.setFloat("uRotation", rotation);
    shader.setVec3("uColor", color[0], color[1], color[2]);

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PatternRenderer::setPatternType(int type) { patternType = type; }
void PatternRenderer::setScale(float s) { scale = s; }
void PatternRenderer::setRotation(float angle) { rotation = angle; }
void PatternRenderer::setColor(float r, float g, float b) {
    color[0] = r; color[1] = g; color[2] = b;
}
GLuint PatternRenderer::getPatternTexture() const { return texture; }

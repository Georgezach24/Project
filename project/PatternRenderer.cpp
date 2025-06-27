#include "PatternRenderer.h"
#include <iostream>

PatternRenderer::PatternRenderer()
    : shader("pattern_gen.vert", "pattern_gen.frag") {
    initQuad();
    initFramebuffer();
}

void PatternRenderer::initQuad() {
    float quad[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f
    };

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
        std::cerr << "[PatternRenderer] ERROR: Framebuffer is not complete!\n";

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
    shader.setFloat("uStripeWidth", stripeWidth);
    shader.setFloat("uCircleRadius", circleRadius);
    shader.setFloat("uTriangleSize", triangleSize);
    shader.setFloat("uHexSize", hexSize);
    shader.setVec3("uColor", color[0], color[1], color[2]);

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int PatternRenderer::getTexture() const {
    return texture;
}

void PatternRenderer::setPatternType(int type) { patternType = type; }
void PatternRenderer::setScale(float s) { scale = s; }
void PatternRenderer::setRotation(float angle) { rotation = angle; }
void PatternRenderer::setStripeWidth(float w) { stripeWidth = w; }
void PatternRenderer::setCircleRadius(float r) { circleRadius = r; }
void PatternRenderer::setTriangleSize(float s) { triangleSize = s; }
void PatternRenderer::setHexSize(float s) { hexSize = s; }
void PatternRenderer::setColor(float r, float g, float b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

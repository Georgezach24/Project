#include "PatternRenderer.h"
#include <glad/glad.h>
#include <iostream>

static const char* vertexShaderSrc = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
)";

static const char* fragmentShaderSrc = R"(
#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D patternTexture;

void main() {
    vec3 texColor = texture(patternTexture, TexCoords).rgb;
    vec3 ambient = 0.1 * texColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * texColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
    vec3 specular = spec * vec3(1.0); // white highlight

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
)";

PatternRenderer::PatternRenderer()
    : shader(vertexShaderSrc, fragmentShaderSrc) {
    initQuad();
    initFramebuffer();
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

void PatternRenderer::initFramebuffer() {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &patternTexture);
    glBindTexture(GL_TEXTURE_2D, patternTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, patternTexture, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1024, 1024);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "ERROR: PatternRenderer framebuffer not complete!\n";

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

unsigned int PatternRenderer::getPatternTexture() const {
    return patternTexture;
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

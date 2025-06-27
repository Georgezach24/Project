#pragma once
#include <glad/glad.h>

class PatternFramebuffer {
public:
    PatternFramebuffer(int width, int height);
    ~PatternFramebuffer();

    void bind();
    void unbind();
    GLuint getTexture() const;

private:
    GLuint fbo = 0;
    GLuint texture = 0;
    GLuint rbo = 0;
    int width, height;
};

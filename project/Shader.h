#pragma once
#include <string>

class Shader {
public:
    Shader(const char* vertexSrc, const char* fragmentSrc);
    void use();
    void setInt(const std::string& name, int value);

private:
    unsigned int id;
    int getUniformLocation(const std::string& name);
};

#pragma once
#include <string>

class Shader {
public:
    Shader(const char* vertexSrc, const char* fragmentSrc);
    void use();
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec3(const std::string& name, float x, float y, float z);

private:
    unsigned int id;
    int getUniformLocation(const std::string& name);
};

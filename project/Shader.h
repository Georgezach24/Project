#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(const char* vertexSrc, const char* fragmentSrc);
    void use();
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec3(const std::string& name, float x, float y, float z);
    void setMat4(const std::string& name, const glm::mat4& mat);

private:
    unsigned int id;
    int getUniformLocation(const std::string& name);
};
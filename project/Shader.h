#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    void use() const;

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec3(const std::string& name, const glm::vec3& vec) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;

private:
    std::string readFile(const char* path);
    void checkCompileErrors(unsigned int shader, const std::string& type);
};

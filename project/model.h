#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Model {
public:
    Model(const std::string& path);
    void Draw() const;

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO = 0, VBO = 0, EBO = 0;

    void loadModel(const std::string& path);
    void setupMesh();
};

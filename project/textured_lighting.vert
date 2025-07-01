#version 330 core

//Layout and input variables for the vertex shader
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

//Output variables to the fragment shader
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

//Uniforms for transformation matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0)); // Transform position to world space
    Normal = mat3(transpose(inverse(model))) * aNormal; // Transform normal to world space
    TexCoords = aTexCoords;// Pass texture coordinates to fragment shader

    gl_Position = projection * view * vec4(FragPos, 1.0); // Transform position to clip space
}

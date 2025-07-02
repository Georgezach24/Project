#version 330 core

out vec4 FragColor; // Output color of the fragment

// Input from vertex shader
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

// Uniforms for lighting
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D patternTexture;
uniform bool useTexture;

void main() {

    vec3 texColor = useTexture ? texture(patternTexture, TexCoords).rgb : vec3(1.0);

    // Ambient Lighting
    vec3 ambient = 0.1 * texColor;

    //Diffuse Lighting 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * texColor;

    // Specular Lighting
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
    vec3 specular = spec * vec3(1.0);

    FragColor = vec4(ambient + diffuse + specular, 1.0); // Combine all lighting components
}

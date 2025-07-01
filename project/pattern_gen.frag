#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform int uPatternType; // 0: stripes, 1: circles, 2: triangles, 3: hexagons
uniform float uScale;
uniform float uRotation;
uniform float uStripeWidth;
uniform float uCircleRadius;
uniform float uTriangleSize;
uniform float uHexSize;
uniform vec3 uColor;

// Function to rotate UV coordinates around the center (0.5, 0.5)
vec2 rotate(vec2 uv, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    mat2 rot = mat2(c, -s, s, c);
    return rot * (uv - 0.5) + 0.5;
}

void main() {
    vec2 uv = TexCoords;
    uv = rotate(uv, uRotation);
    uv *= uScale;

    float pattern = 0.0;

    //If the pattern type is not set, default to stripes    
    if (uPatternType == 0) {
        pattern = step(uStripeWidth, fract(uv.x));   
    } else if (uPatternType == 1) { // Stripes are created by checking the fractional part of the x coordinate 
        vec2 center = fract(uv) - 0.5;
        pattern = step(length(center), uCircleRadius);
    } else if (uPatternType == 2) { // Triangles are created by checking the fractional part of the x coordinate
        vec2 p = fract(uv);
        float triangle = step(p.y, p.x) * step(p.y, 1.0 - p.x);
        pattern = triangle;
    }else if (uPatternType == 3) { // Hexagons are created by transforming the UV coordinates to a hexagonal grid
        vec2 q = vec2(uv.x * 2.0 / (3.0 * uHexSize),
                    (uv.y - mod(floor(uv.x / (1.5 * uHexSize)), 2.0) * 0.5 * sqrt(3.0) * uHexSize) / (sqrt(3.0) * uHexSize));

        vec2 hex = fract(q) - 0.5;
        vec2 id = floor(q);

        // Stretching to hexagonal grid
        float a = abs(hex.x);
        float b = abs(hex.y);
        bool isInside = b + a * 0.57735 < 0.5;

        pattern = isInside ? 1.0 : 0.0;
    }

    FragColor = vec4(uColor * pattern, 1.0); // Output the color based on the pattern
}

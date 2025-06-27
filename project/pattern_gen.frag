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

    if (uPatternType == 0) {
        pattern = step(uStripeWidth, fract(uv.x));
    } else if (uPatternType == 1) {
        vec2 center = fract(uv) - 0.5;
        pattern = step(length(center), uCircleRadius);
    } else if (uPatternType == 2) {
        vec2 p = fract(uv);
        float triangle = step(p.y, p.x) * step(p.y, 1.0 - p.x);
        pattern = triangle * step(uTriangleSize, 0.5);
    } else if (uPatternType == 3) {
        vec2 p = mod(uv, uHexSize) - 0.5 * uHexSize;
        float d = abs(p.x * 0.866025 + p.y * 0.5) + abs(p.y);
        pattern = step(d, uHexSize * 0.5);
    }

    FragColor = vec4(uColor * pattern, 1.0);
}

#version 410 core

layout(location = 0) in vec2 aPos0;
layout(location = 1) in vec2 aPos1;
layout(location = 2) in uint aColor;
layout(location = 3) in float aThickness;
layout(location = 4) in float aDepth;
layout(location = 5) in vec3 aFillPos;
layout(location = 6) in uint aFillColor;

out vec2 vPos0;
out vec2 vPos1;
out vec4 vertexColor;
out vec2 vertexThickness;
out float vertexDepth;
out vec3 vFillPos;
out vec4 vertexFillColor;

uniform float screen_x;
uniform float screen_y;
uniform float w;

void main() {
    vec2 scale = vec2(2 / screen_x, 2 / screen_y);

    vPos0 = aPos0 * scale;
    vPos1 = aPos1 * scale;
    vertexColor = vec4(
        float((aColor >> 24) & uint(0xFF)),
        float((aColor >> 16) & uint(0xFF)),
        float((aColor >> 8) & uint(0xFF)),
        float(aColor & uint(0xFF))
    ) / 255.0;
    vertexThickness = aThickness * scale;
    vertexDepth = aDepth / w;
    vFillPos = aFillPos * vec3(scale, 1.0 / w);
    vertexFillColor = vertexFillColor = vec4(
        float((aFillColor >> 24) & uint(0xFF)),
        float((aFillColor >> 16) & uint(0xFF)),
        float((aFillColor >> 8) & uint(0xFF)),
        float(aFillColor & uint(0xFF))
    ) / 255.0;

    gl_Position = vec4(aPos0 * scale, aDepth / w, 1.0);
}
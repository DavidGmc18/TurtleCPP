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
out float vertexThickness;
out float vertexDepth;
out vec3 vFillPos;
out vec4 vertexFillColor;

uniform float w;

void main() {
    vPos0 = aPos0;
    vPos1 = aPos1;
    vertexColor = vec4(
        float((aColor >> 24) & uint(0xFF)),
        float((aColor >> 16) & uint(0xFF)),
        float((aColor >> 8) & uint(0xFF)),
        float(aColor & uint(0xFF))
    ) / 0xFF;
    vertexThickness = aThickness / 2;
    vertexDepth = aDepth / w;
    vFillPos = aFillPos * vec3(1.0, 1.0, 1.0 / w);
    vertexFillColor = vertexFillColor = vec4(
        float((aFillColor >> 24) & uint(0xFF)),
        float((aFillColor >> 16) & uint(0xFF)),
        float((aFillColor >> 8) & uint(0xFF)),
        float(aFillColor & uint(0xFF))
    ) / 0xFF;

    gl_Position = vec4(aPos0, aDepth / w, 1.0);
}
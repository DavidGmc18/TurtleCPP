#version 450 core

layout(location = 0) in vec2 aPos0;
layout(location = 1) in vec2 aPos1;
layout(location = 2) in vec4 aColor;
layout(location = 3) in float aThickness;
layout(location = 4) in float aDepth;
layout(location = 5) in vec2 aFillPos;
layout(location = 6) in vec4 aFillColor;

out vec2 vPos0;
out vec2 vPos1;
out vec4 vertexColor;
out vec2 vertexThickness;
out float vertexDepth;
out vec2 vFillPos;
out vec4 vertexFillColor;

uniform float screen_x;
uniform float screen_y;

void main() {
    vec2 scale = vec2(2 / screen_x, 2 / screen_y);

    vPos0 = aPos0 * scale;
    vPos1 = aPos1 * scale;
    vertexColor = aColor;
    vertexThickness = aThickness * scale;
    vertexDepth = aDepth;
    vFillPos = aFillPos * scale;
    vertexFillColor = aFillColor;

    gl_Position = vec4(aPos0 * scale, aDepth, 1.0);
}
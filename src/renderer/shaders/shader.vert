#version 450 core

layout(location = 0) in vec2 aPos0;
layout(location = 1) in vec2 aPos1;
layout(location = 2) in vec4 aColor;
layout(location = 3) in float aThickness;
layout(location = 4) in float aDepth;

out vec2 vPos0;
out vec2 vPos1;
out vec4 vertexColor;
out float vertexThickness;
out float vertexDepth;

void main() {
    vPos0 = aPos0;
    vPos1 = aPos1;
    vertexColor = aColor;
    vertexThickness = aThickness;
    vertexDepth = aDepth;

    gl_Position = vec4(aPos0, aDepth, 1.0);
}
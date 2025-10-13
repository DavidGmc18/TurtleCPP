#version 450 core

layout(points) in;
layout(triangle_strip, max_vertices=4) out;

in vec2 vPos0[];
in vec2 vPos1[];
in vec4 vertexColor[];
in float vertexThickness[];
in float vertexDepth[];

out vec4 fragColor;

uniform float screen_x;
uniform float screen_y;

void main() {
    vec2 p0 = vPos0[0];
    vec2 p1 = vPos1[0];

    vec2 t = vec2(vertexThickness[0] / screen_x, vertexThickness[0] / screen_y);

    vec2 dir = normalize(p1 - p0);
    vec2 perp = vec2(-dir.y, dir.x);

    vec2 offset = perp * t;

    if (vertexColor[0].w > 0.0) {
        fragColor = vertexColor[0];
        gl_Position = vec4(p0 + offset, vertexDepth[0], 1.0); EmitVertex();
        gl_Position = vec4(p1 + offset, vertexDepth[0], 1.0); EmitVertex();
        gl_Position = vec4(p0 - offset, vertexDepth[0], 1.0); EmitVertex();
        gl_Position = vec4(p1 - offset, vertexDepth[0], 1.0); EmitVertex();
        EndPrimitive();
    }
}
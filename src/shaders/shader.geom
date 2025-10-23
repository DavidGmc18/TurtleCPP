#version 450 core

layout(points) in;
layout(triangle_strip, max_vertices=7) out;

in vec2 vPos0[];
in vec2 vPos1[];
in vec4 vertexColor[];
in vec2 vertexThickness[];
in float vertexDepth[];
in vec3 vFillPos[]; 
in vec4 vertexFillColor[];

out vec4 fragColor;

void main() {
    vec2 p0 = vPos0[0];
    vec2 p1 = vPos1[0];

    vec2 dir = normalize(p1 - p0);
    vec2 perp = vec2(-dir.y, dir.x);

    vec2 offset = perp * vertexThickness[0] / 2;

    if (vertexColor[0].w > 0.0) {
        fragColor = vertexColor[0];
        gl_Position = vec4(p0 + offset, vertexDepth[0], 1.0); EmitVertex();
        gl_Position = vec4(p1 + offset, vertexDepth[0], 1.0); EmitVertex();
        gl_Position = vec4(p0 - offset, vertexDepth[0], 1.0); EmitVertex();
        gl_Position = vec4(p1 - offset, vertexDepth[0], 1.0); EmitVertex();
        EndPrimitive();
    }

    if (vertexFillColor[0].w > 0.0) {
        fragColor = vertexFillColor[0];
        gl_Position = vec4(p0, vFillPos[0].z, 1.0); EmitVertex();
        gl_Position = vec4(p1, vFillPos[0].z, 1.0); EmitVertex();
        gl_Position = vec4(vFillPos[0], 1.0); EmitVertex();
        EndPrimitive();
    }
}
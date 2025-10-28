#version 410 core

layout(points) in;
layout(triangle_strip, max_vertices=103) out;

in vec2 vPos0[];
in vec2 vPos1[];
in vec4 vertexColor[];
in float vertexThickness[];
in float vertexDepth[];
in vec3 vFillPos[]; 
in vec4 vertexFillColor[];

float pi = 3.14159265358979323846;
uniform float screen_x;
uniform float screen_y;
vec2 scale = vec2(2 / screen_x, 2 / screen_y);

out vec4 fragColor;

vec2 rotate(vec2 v, float angle) {
    float c = cos(angle);
    float s = sin(angle);
    return vec2(v.x * c - v.y * s, v.x * s + v.y * c);
}

void main() {
    vec2 p0 = vPos0[0];
    vec2 p1 = vPos1[0];

    if (vertexFillColor[0].w > 0.0) {
        fragColor = vertexFillColor[0];
        gl_Position = vec4(p0 * scale, vFillPos[0].z, 1.0); EmitVertex();
        gl_Position = vec4(p1 * scale, vFillPos[0].z, 1.0); EmitVertex();
        gl_Position = vec4(vFillPos[0] * vec3(scale, 1.0), 1.0); EmitVertex();
        EndPrimitive();
    }

    if (vertexColor[0].w > 0.0) {
        fragColor = vertexColor[0];
        vec2 dir = normalize(p1 - p0);
        vec2 perp = vec2(-dir.y, dir.x);
        vec2 offset = perp * vertexThickness[0];

        gl_Position = vec4((p0 + offset) * scale, vertexDepth[0], 1.0); EmitVertex();
        gl_Position = vec4((p1 + offset) * scale, vertexDepth[0], 1.0); EmitVertex();
        gl_Position = vec4((p0 - offset) * scale, vertexDepth[0], 1.0); EmitVertex();
        gl_Position = vec4((p1 - offset) * scale, vertexDepth[0], 1.0); EmitVertex();
        EndPrimitive();

        int num_segments = clamp(int(vertexThickness[0]), 1, 16);

        for (int i=0; i<num_segments; i++) {
            float alpha0 = float(i) / num_segments * pi;
            float alpha1 = float(i+1) / num_segments * pi;
            
            gl_Position = vec4(p0 * scale, vertexDepth[0], 1.0); EmitVertex();
            gl_Position = vec4((p0 + rotate(perp, alpha0) * vertexThickness[0]) * scale, vertexDepth[0], 1.0); EmitVertex();
            gl_Position = vec4((p0 + rotate(perp, alpha1) * vertexThickness[0]) * scale, vertexDepth[0], 1.0); EmitVertex();
            EndPrimitive();
        }

        for (int i=0; i<num_segments; i++) {
            float alpha0 = float(i) / num_segments * pi;
            float alpha1 = float(i+1) / num_segments * pi;
            
            gl_Position = vec4(p1 * scale, vertexDepth[0], 1.0); EmitVertex();
            gl_Position = vec4((p1 + rotate(-perp, alpha0) * vertexThickness[0]) * scale, vertexDepth[0], 1.0); EmitVertex();
            gl_Position = vec4((p1 + rotate(-perp, alpha1) * vertexThickness[0]) * scale, vertexDepth[0], 1.0); EmitVertex();
            EndPrimitive();
        }
    }
}
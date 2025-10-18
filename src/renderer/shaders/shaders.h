#pragma once
#ifdef BACKEND_GL

#include "../glad/glad.h"
#include <stdio.h>

extern const char* shader_vert_src;
extern const char* shader_geom_src;
extern const char* shader_frag_src;

inline GLuint compileShader(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        fprintf(stderr, "Shader compilation failed:\n%s\n", infoLog);
    }
    return shader;
}

inline GLuint createShaderProgram(const char* vertexSrc, const char* geometrySrc, const char* fragmentSrc) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint geometryShader = compileShader(GL_GEOMETRY_SHADER, geometrySrc);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, geometryShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        fprintf(stderr, "Program linking failed:\n%s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(geometryShader);
    glDeleteShader(fragmentShader);
    return program;
}

#endif
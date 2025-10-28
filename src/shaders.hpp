#pragma once

#include "glad/glad.h"

namespace turtle {

extern const char* shader_vert_src;
extern const char* shader_geom_src;
extern const char* shader_frag_src;

GLuint compileShader(GLenum type, const char* src);
GLuint createShaderProgram(const char* vertexSrc, const char* geometrySrc, const char* fragmentSrc);

}
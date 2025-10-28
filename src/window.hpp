#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

extern GLFWwindow* window;
extern int screen_x;
extern int screen_y;

extern GLuint vao;
extern GLuint vbo;
extern GLuint w_uniform;

constexpr uint32_t VECTOR_SIZE = 11;

void create_window(uint32_t& framerate, uint32_t multisample);
void gl_setup(uint64_t total_num_lines);
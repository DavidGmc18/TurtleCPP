#include "window.hpp"
#include "shaders.hpp"
#include <stdio.h>

namespace turtle {

GLFWwindow* window = nullptr;

GLuint vao = 0;
GLuint vbo = 0;
GLuint w_uniform = 0;

void create_window(uint32_t& framerate, uint32_t multisample) {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, multisample);
   
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window = glfwCreateWindow(screen_x, screen_y, "Turtle", nullptr, nullptr);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // VSync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        glfwTerminate();
        return;
    }

    if (framerate == 0) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        if (!monitor) {
            fprintf(stderr, "No primary monitor found\n");
            glfwTerminate();
            return;
        }

        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        if (!mode) {
            fprintf(stderr, "Could not get video mode\n");
            glfwTerminate();
            return;
        }

        framerate = mode->refreshRate;

        if (framerate == 0) {
            framerate = 60;
            printf("Automatic framerate detection failed, defaulting to %iHz\n", framerate);
        } else {
            #ifdef DEBUG
            printf("Automatically detected framerate: %iHz\n", framerate);
            #endif
        }
    }
}

void gl_setup(uint64_t total_num_lines) {
    GLuint shaderProgram = createShaderProgram(shader_vert_src, shader_geom_src, shader_frag_src);
    GLuint locX = glGetUniformLocation(shaderProgram, "screen_x");
    GLuint locY = glGetUniformLocation(shaderProgram, "screen_y");
    w_uniform = glGetUniformLocation(shaderProgram, "w");
    glUseProgram(shaderProgram);
    glUniform1f(locX, float(screen_x));
    glUniform1f(locY, float(screen_y));

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_MULTISAMPLE);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, total_num_lines * VECTOR_SIZE * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, VECTOR_SIZE * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VECTOR_SIZE * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, VECTOR_SIZE * sizeof(float), (void*)(4 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, VECTOR_SIZE * sizeof(float), (void*)(5*sizeof(float)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, VECTOR_SIZE * sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, VECTOR_SIZE * sizeof(float), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(6, 1, GL_UNSIGNED_INT, VECTOR_SIZE * sizeof(float), (void*)(10 * sizeof(float)));
    glEnableVertexAttribArray(6);

    glBindVertexArray(0);
}

}
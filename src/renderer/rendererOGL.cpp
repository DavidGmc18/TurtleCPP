#ifdef BACKEND_GL
#include "turtle.hpp"
#include "renderer.hpp"
#include "shaders/shaders.h"
#include <string.h>
#include <chrono>
#include <iostream>
#include <thread>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#ifdef DEBUG
#include <algorithm>
#include <numeric>
#endif

static int screen_x = 800;
static int screen_y = 600;
static float screen_r = 1.0f;
static float screen_g = 1.0f;
static float screen_b = 1.0f;

void screen_size(int x, int y) {
    screen_x = x;
    screen_y = y;
}

void bgcolor(Color color) {
    screen_r = float((color.rgba >> 24) & 0xFF) / 255.0f;
    screen_g = float((color.rgba >> 16) & 0xFF) / 255.0f;
    screen_b = float((color.rgba >> 8) & 0xFF) / 255.0f;
}

void mainloop(int framerate) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(screen_x, screen_y, "Turtle", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // VSync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        glfwTerminate();
        return;
    }

    GLuint shaderProgram = createShaderProgram(shader_vert_src, shader_geom_src, shader_frag_src);
    GLuint locX = glGetUniformLocation(shaderProgram, "screen_x");
    GLuint locY = glGetUniformLocation(shaderProgram, "screen_y");
    glUseProgram(shaderProgram);
    glUniform1f(locX, float(screen_x));
    glUniform1f(locY, float(screen_y));

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    #ifdef DEBUG
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
    constexpr int FRAMETIMES_SIZE = 100;
    int frameIndex = 0;
    float frameTimes[FRAMETIMES_SIZE] = {};
    #endif

    constexpr uint VECTOR_SIZE = 11;

    const uint num_turtles = Turtle::turtles().size();

    uint step[num_turtles];
    memset(step, 0, num_turtles * sizeof(uint));

    uint n = 0;
    for (int t = 0; t < num_turtles; ++t) {
        n += Turtle::turtles()[t]->get_points().size() - 1;
    }
    const uint total_num_lines = n;
    float lines[total_num_lines * VECTOR_SIZE];
    uint num_lines = 0;

    float depth = 0.0f;

    uint current_line_indicies[num_turtles];

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lines), nullptr, GL_DYNAMIC_DRAW);

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

    float fill_start_pos[3 * num_turtles];
    memset(fill_start_pos, 0.0f, 3 * num_turtles * sizeof(float));

    using clock = std::chrono::high_resolution_clock;
    const std::chrono::microseconds frameDuration(1000000 / framerate);
    auto frameStart = clock::now();
    while (!glfwWindowShouldClose(window)) {
        for (int t = 0; t < num_turtles; ++t) {
            Turtle turtle = *Turtle::turtles()[t];
            for (uint p = step[t]; p + 1 < turtle.get_points().size(); ++p) {
                const std::vector<Point> points = turtle.get_points();
                if (!(points[p].fill_rgba & 0xFF) && (points[p+1].fill_rgba & 0x000000FF)) {
                    fill_start_pos[t*2] = points[p+1].x;
                    fill_start_pos[t*2+1] = points[p+1].y;
                    fill_start_pos[t*3+2] = depth; //TODO is depth correctly intitaliazed for id=0 fill?
                }

                lines[num_lines*VECTOR_SIZE    ] = points[p].x;
                lines[num_lines*VECTOR_SIZE + 1] = points[p].y;

                lines[num_lines*VECTOR_SIZE + 2] = points[p+1].x;
                lines[num_lines*VECTOR_SIZE + 3] = points[p+1].y;

                memcpy(lines + num_lines*VECTOR_SIZE + 4, &points[p].rgba, sizeof(float));

                lines[num_lines*VECTOR_SIZE + 5] = points[p].thickness;

                lines[num_lines*VECTOR_SIZE + 6] = depth; // TODO

                lines[num_lines*VECTOR_SIZE + 7] = fill_start_pos[t*3];
                lines[num_lines*VECTOR_SIZE + 8] = fill_start_pos[t*3+1];
                lines[num_lines*VECTOR_SIZE + 9] = fill_start_pos[t*3+2];

                memcpy(lines + num_lines*VECTOR_SIZE + 10, &points[p].fill_rgba, sizeof(float));

                num_lines++;
                step[t]++;
            }
        }

        glClearColor(screen_r, screen_g, screen_b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, num_lines * VECTOR_SIZE * sizeof(float), lines);

        glBindVertexArray(vao);
        glDrawArrays(GL_POINTS, 0, num_lines);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        auto frameEnd = clock::now();
        auto frameTime = std::chrono::duration_cast<std::chrono::microseconds>(frameEnd - frameStart);
        if (frameTime < frameDuration) {
            std::this_thread::sleep_for(frameDuration - frameTime);
        }
        frameStart = clock::now();

        #ifdef DEBUG
        frameTimes[frameIndex] = frameTime.count() / 1000.0f;
        frameIndex++;
        if (frameIndex >= FRAMETIMES_SIZE) {
            frameIndex = 0;
            float avg = std::accumulate(frameTimes, frameTimes + FRAMETIMES_SIZE, 0.0f) / FRAMETIMES_SIZE;
            float max = *std::max_element(frameTimes, frameTimes + FRAMETIMES_SIZE);
            float min = *std::min_element(frameTimes, frameTimes + FRAMETIMES_SIZE);
            printf("Frame time(%i) ->  MIN %.3fms  AVG %.3fms  MAX %.3fms\n", FRAMETIMES_SIZE, min, avg, max);
        }
        #endif
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
#endif
#pragma once


#include "renderer.hpp"
#include <cmath>
#include <cstdint>
#include <sys/types.h>
#include <vector>

struct Point {
    float x = 0.0f;
    float y = 0.0f;
    float angle = 0.0f;
    bool pen = true;;
    uint32_t rgba = 0x000000FF;
    float thickness = 1;
};

class Turtle {
protected:
    static std::vector<Turtle*> all_turtles;

    std::vector<Point> points = {Point{0, 0, 0, true}};

public:
    uint speed = 100;
    uint32_t rgba = 0x000000FF;

    Turtle();

    static const std::vector<Turtle*>& get_all_turtles();
    std::vector<Point> get_points();

    void forward(float d);
    void backward(float d);

    void left(float a);
    void right(float a);

    void penup();
    void pendown();

    void pencolor(uint32_t rgba_);
    void pencolor(uint8_t r, uint8_t g, uint8_t b);

    void color(uint32_t rgba_);
    void color(uint8_t r, uint8_t g, uint8_t b);

    void set_speed(int v);

    void go_to(float x, float y);

    void penwidth(float w);
};
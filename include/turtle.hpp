#pragma once

#include "color.hpp"
#include <cstdint>
#include <sys/types.h>
#include <vector>

struct Point {
    float x = 0.0f;
    float y = 0.0f;
    float angle = 0.0f;
    uint32_t rgba = 0x000000FF;
    float thickness = 1;
    uint32_t fill_rgba = 0x00000000;
};

class Turtle {
protected:
    static std::vector<Turtle*> all_turtles;

    std::vector<Point> points = {Point{}};

public:
    float speed = 100;
    uint32_t rgba = 0x000000FF;

    Turtle();

    static const std::vector<Turtle*>& turtles();
    const std::vector<Point>& get_points() const;

    void forward(float d);
    void backward(float d);

    void left(float a);
    void right(float a);

    void penup();
    void pendown();

    void pencolor(Color color);

    void color(Color color);

    void set_speed(float v);

    void go_to(float x, float y);

    void penwidth(float w);

    void circle(float radius, float extent = 360, int steps = 90);

    void begin_fill();
    void end_fill();
    void fillcolor(Color color);
};

void screen_size(int x, int y);
void bgcolor(Color color);

void mainloop(int framerate = 60);
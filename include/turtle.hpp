#pragma once

#include "color.hpp"
#include <cstdint>
#include <vector>
#include "turtle_api.hpp"

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

    TURTLE_API Turtle();

    static const std::vector<Turtle*>& turtles();
    const std::vector<Point>& get_points() const;

    TURTLE_API void forward(float d);
    TURTLE_API void backward(float d);

    TURTLE_API void left(float a);
    TURTLE_API void right(float a);

    TURTLE_API void penup();
    TURTLE_API void pendown();

    TURTLE_API void pencolor(Color color);

    TURTLE_API void color(Color color);

    TURTLE_API void set_speed(float v);

    TURTLE_API void go_to(float x, float y);

    TURTLE_API void penwidth(float w);

    TURTLE_API void circle(float radius, float extent = 360, int steps = 90);

    TURTLE_API void begin_fill();
    TURTLE_API void end_fill();
    TURTLE_API void fillcolor(Color color);
};

TURTLE_API void screen_size(int x, int y);
TURTLE_API void bgcolor(Color color);

TURTLE_API void mainloop(uint32_t framerate = 0, uint32_t multisample = 4);
#pragma once

#include "color.hpp"
#include <cstdint>
#include "turtle_api.hpp"

class Turtle {
private:
    const uint32_t id;
public:
    TURTLE_API Turtle();

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
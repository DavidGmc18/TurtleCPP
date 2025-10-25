#pragma once

#include <vector>

struct Point {
    float x = 0.0f;
    float y = 0.0f;
    float angle = 0.0f;
    uint32_t rgba = 0x000000FF;
    float thickness = 1;
    uint32_t fill_rgba = 0x00000000;
};

struct TurtleImpl {
    float speed = 100;
    uint32_t rgba = 0x000000FF;
    std::vector<Point> points = {Point{}};
};

extern std::vector<TurtleImpl> all_turtles;
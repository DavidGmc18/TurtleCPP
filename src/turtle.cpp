#include "turtle.hpp"
#include "turtle_impl.hpp"
#include "color.hpp"
#include <cmath>

std::vector<TurtleImpl> all_turtles;

Turtle::Turtle(): id(all_turtles.size()) {
    all_turtles.push_back(TurtleImpl{}); 
}

void Turtle::forward(float d) {
    Point new_point = all_turtles[id].points.back();
    float angle = new_point.angle * M_PI / 180.0f;
    new_point.x += d * sin(angle);
    new_point.y += d * cos(angle);
    all_turtles[id].points.push_back(new_point);
}

void Turtle::backward(float d) {
    Point new_point = all_turtles[id].points.back();
    float angle = new_point.angle * M_PI / 180.0f;
    new_point.x += -d * sin(angle);
    new_point.y += -d * cos(angle);
    all_turtles[id].points.push_back(new_point);
}

void Turtle::left(float a) {
    all_turtles[id].points.back().angle -= a;
}

void Turtle::right(float a) {
    all_turtles[id].points.back().angle += a;
}

void Turtle::penup() {
    all_turtles[id].points.back().rgba &= 0xFFFFFF00;
}

void Turtle::pendown() {
    all_turtles[id].points.back().rgba &= 0xFFFFFF00;
    all_turtles[id].points.back().rgba |= 0xFF;
}

void Turtle::pencolor(Color color) {
    uint8_t alpha = all_turtles[id].points.back().rgba & 0x000000FF;
    all_turtles[id].points.back().rgba = (color.rgba & 0xFFFFFF00) | alpha;
}

void Turtle::color(Color color) {
    all_turtles[id].rgba = color.rgba;
}

void Turtle::set_speed(float v) {
    all_turtles[id].speed = v;
}

void Turtle::go_to(float x, float y) {
    Point new_point = all_turtles[id].points.back();
    new_point.x = x;
    new_point.y = y;
    all_turtles[id].points.push_back(new_point);
}

void Turtle::penwidth(float w) {
    all_turtles[id].points.back().thickness = w;
}

void Turtle::circle(float radius, float extent, int steps) {
    float angle = extent / steps;
    float distane = 2 * sin((angle / 2) * M_PI / 180.0f) * radius;
    if (distane > 0) {
        right(angle / 2);
        for (int i = 0; i < steps; ++i) {
            left(angle);
            forward(distane);
        }
        left(angle / 2);
    } else {
        left(angle / 2);
        for (int i = 0; i < steps; ++i) {
            right(angle);
            forward(-distane);
        }
        right(angle / 2);
    }
}

void Turtle::begin_fill() {
    all_turtles[id].points.back().fill_rgba &= 0xFFFFFF00;
    all_turtles[id].points.back().fill_rgba |= 0xFF;
}

void Turtle::end_fill() {
    all_turtles[id].points.back().fill_rgba &= 0xFFFFFF00;
}

void Turtle::fillcolor(Color color) {
    uint8_t alpha = all_turtles[id].points.back().fill_rgba & 0x000000FF;
    all_turtles[id].points.back().fill_rgba = (color.rgba & 0xFFFFFF00) | alpha;
}
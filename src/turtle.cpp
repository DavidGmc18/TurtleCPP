#include "turtle.hpp"

std::vector<Turtle*> Turtle::all_turtles = {};

Turtle::Turtle() {
    all_turtles.push_back(this);
}

const std::vector<Turtle*>& Turtle::get_all_turtles() {
    return all_turtles;
}

std::vector<Point> Turtle::get_points() {
    return points;
}

void Turtle::forward(float d) {
    Point new_point = points.back();
    float angle = new_point.angle * M_PI / 180.0f;
    new_point.x += d * sin(angle);
    new_point.y += d * cos(angle);
    points.push_back(new_point);
}

void Turtle::backward(float d) {
    Point new_point = points.back();
    float angle = new_point.angle * M_PI / 180.0f;
    new_point.x += -d * sin(angle);
    new_point.y += -d * cos(angle);
    points.push_back(new_point);
}

void Turtle::left(float a) {
    points.back().angle -= a;
}

void Turtle::right(float a) {
    points.back().angle += a;
}

void Turtle::penup() {
    points.back().pen = false;
}

void Turtle::pendown() {
    points.back().pen = true;
}

void Turtle::pencolor(uint32_t color) {
    points.back().rgba = color;
}

void Turtle::pencolor(uint8_t r, uint8_t g, uint8_t b) {
    points.back().rgba = ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | 0xFF;
}

void Turtle::color(uint32_t color) {
    rgba = color;
}

void Turtle::color(uint8_t r, uint8_t g, uint8_t b) {
    rgba = ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | 0xFF;
}

void Turtle::set_speed(int v) {
    speed = v;
}

void Turtle::go_to(float x, float y) {
    Point new_point = points.back();
    new_point.x = x;
    new_point.y = y;
    points.push_back(new_point);
}

void Turtle::penwidth(float w) {
    points.back().thickness = w;
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
#pragma once

#include <cstdint>

struct Color {
    uint32_t rgba = 0x000000FF;

    Color(uint8_t rgb[3]);
    Color(uint8_t r, uint8_t g, uint8_t b);
    Color(const char* color);
};
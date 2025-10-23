#pragma once

#include <cstdint>
#include "turtle_api.hpp"

struct Color {
    uint32_t rgba = 0x000000FF;

    TURTLE_API Color(uint8_t rgb[3]);
    TURTLE_API Color(uint8_t r, uint8_t g, uint8_t b);
    TURTLE_API Color(const char* color);
};
#pragma once

#include <cstdint>

#ifdef _WIN32
#ifdef TURTLE_EXPORTS
    #define TURTLE_API __declspec(dllexport)
#else
    #define TURTLE_API __declspec(dllimport)
#endif
#else
#define TURTLE_API
#endif

namespace turtle {

struct Color {
    uint32_t rgba = 0x000000FF;

    TURTLE_API Color(uint8_t rgb[3]);
    TURTLE_API Color(uint8_t r, uint8_t g, uint8_t b);
    TURTLE_API Color(const char* color);
};
    
}
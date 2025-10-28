#include "turtle/color.hpp"
#include "../generated/color_map.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

namespace turtle {

Color::Color(uint8_t rgb[3]) {
    rgba = ((rgb[0] & 0xFF) << 24) | ((rgb[1] & 0xFF) << 16) | ((rgb[2] & 0xFF) << 8) | 0xFF;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b) {
    rgba = ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | 0xFF;
}

std::string to_lowercase(const char* s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c){ return std::tolower(c); });
    return result;
}

Color::Color(const char* color) {
    std::string color_lower = to_lowercase(color);
    if (color_map.find(color_lower) != color_map.end()) {
        rgba = color_map.at(color_lower);
    } else {
        std::cerr << "WARN: '" << color_lower << "' is not recognized color\n";
    }
}

}
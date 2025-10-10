#pragma once

#include "color.hpp"

void screen_size(int x, int y);
void bgcolor(Color color);

void mainloop(int framerate = 60);
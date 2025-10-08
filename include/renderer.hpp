#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

void screen_size(int x, int y);
void bgcolor(uint32_t);
void bgcolor(uint8_t r, uint8_t g, uint8_t b);

void draw_turtle(struct Window& window, float x, float y, float angle, Uint32 rgba);

void mainloop(int framerate = 60);
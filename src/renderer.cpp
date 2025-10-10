#include "renderer.hpp"
#include "turtle.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cstring>

static int screen_x = 800;
static int screen_y = 600;
static int screen_rgba = 0xFFFFFFFF;

void screen_size(int x, int y) {
    screen_x = x;
    screen_y = y;
}

void bgcolor(uint32_t color) {
    screen_rgba = color;
}

void bgcolor(uint8_t r, uint8_t g, uint8_t b) {
    screen_rgba = ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | 0xFF;
}

void draw_turtle(SDL_Renderer* renderer, float x, float y, float angle, Uint32 rgba) {
    float f = 20; // front
    float mb = -5; // middle-back
    float sb = 15; // sides-back
    float w = 12; // width

    angle *= M_PI / 180.0f;

    float x1 = x - -f*sin(angle);
    float y1 = y + -f*cos(angle);

    float x2 = x + -w*cos(angle) - sb*sin(angle);
    float y2 = y + -w*sin(angle) + sb*cos(angle);

    float x3 = x - -mb*sin(angle);
    float y3 = y + -mb*cos(angle);

    float x4 = x + w*cos(angle) - sb*sin(angle);
    float y4 = y + w*sin(angle) + sb*cos(angle);

    SDL_SetRenderDrawColor(renderer, rgba >> 24, rgba >> 16, rgba >> 8, rgba);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
    SDL_RenderDrawLine(renderer, x3, y3, x4, y4);
    SDL_RenderDrawLine(renderer, x4, y4, x1, y1);
}

void mainloop(int framerate) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("Turtle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_x, screen_y, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    bool running = true;
    SDL_Event e;

    std::vector<uint> step(Turtle::get_all_turtles().size(), 0);
    std::vector<Uint32> start(Turtle::get_all_turtles().size(), 0);
    for (int idx = 0; idx < Turtle::get_all_turtles().size(); ++idx) {
        start[idx] = SDL_GetTicks();
    }

    std::vector<float> distance(Turtle::get_all_turtles().size(), 0);

    const float frameDelay = 1000.0f / framerate;
    while (running) {
        Uint32 frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        SDL_SetRenderDrawColor(renderer, screen_rgba >> 24, screen_rgba >> 16, screen_rgba >> 8, screen_rgba);
        SDL_RenderClear(renderer);

        for (int idx = 0; idx < Turtle::get_all_turtles().size(); ++idx) {
            Turtle* t = Turtle::get_all_turtles()[idx];
            for (uint i = 0; i + 1 < t->get_points().size(); ++i) {
                float x1 = t->get_points()[i].x + float(screen_x)/2;
                float y1 = -(t->get_points()[i].y) + float(screen_y)/2;
                float x2, y2;
                if (t->speed == 0 || i < step[idx]) {
                    if (t->speed == 0) step[idx]++;
                    x2 = t->get_points()[i+1].x + float(screen_x)/2;
                    y2 = -(t->get_points()[i+1].y) + float(screen_y)/2;
                } else if (i == step[idx]) {
                    float dx = t->get_points()[i+1].x - t->get_points()[i].x;
                    float dy = -(t->get_points()[i+1].y) + (t->get_points()[i].y);
                    float d = sqrtf(pow(dx, 2) + pow(dy, 2));

                    float wd = t->speed * (SDL_GetTicks() - start[idx]) / 1000.0f;
                    float r = (wd - distance[idx]) / d;

                    if (r >= 1) {
                        step[idx]++;
                        r = 1;
                        distance[idx] += d;
                    } else if (r < 0) {
                        r = 0;
                    }

                    x2 = dx * r + x1;
                    y2 = dy * r + y1;
                }

                if ((i <= step[idx] || t->speed == 0) && t->get_points()[i].pen) {
                    if (t->get_points()[i].thickness == 1) {
                        SDL_SetRenderDrawColor(renderer, t->get_points()[i].rgba >> 24, t->get_points()[i].rgba >> 16, t->get_points()[i].rgba >> 8, t->get_points()[i].rgba);
                        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
                    } else {
                        thickLineRGBA(renderer, x1, y1, x2, y2, t->get_points()[i].thickness, t->get_points()[i].rgba >> 24, t->get_points()[i].rgba >> 16, t->get_points()[i].rgba >> 8, t->get_points()[i].rgba);
                        filledCircleRGBA(renderer, x1, y1, t->get_points()[i].thickness / 2 - 1, t->get_points()[i].rgba >> 24, t->get_points()[i].rgba >> 16, t->get_points()[i].rgba >> 8, t->get_points()[i].rgba);
                        filledCircleRGBA(renderer, x2, y2, t->get_points()[i].thickness / 2 - 1, t->get_points()[i].rgba >> 24, t->get_points()[i].rgba >> 16, t->get_points()[i].rgba >> 8, t->get_points()[i].rgba);
                    }
                }
                
                if (i == step[idx] || (i < step[idx] && i + 2 == t->get_points().size())) {
                    draw_turtle(renderer, x2, y2, t->get_points()[i].angle, t->rgba);
                }
            }
        }

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }

        SDL_RenderPresent(renderer);
    }
}
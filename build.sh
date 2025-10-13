#!/bin/bash

set -e

mkdir -p build
cd "build" || exit 1

# SDL
find ../src -type f \( -name '*.cpp' -o -name '*.c' \) | while read -r f; do
    g++ -DDEBUG -DBACKEND_SDL -fPIC $(sdl2-config --cflags) -I../include -c "$f" -o "$(basename "$f").o"
done

g++ -shared -o libturtle_sdl.so *.o -lSDL2_gfx $(sdl2-config --libs) -lm -ldl -lpthread

rm -f *.o


# openGL
find ../src -type f \( -name '*.cpp' -o -name '*.c' \) | while read -r f; do
    g++ -DDEBUG -DBACKEND_GL -fPIC $(sdl2-config --cflags) -I../include -c "$f" -o "$(basename "$f").o"
done

../gen_shaders.sh src/renderer/shaders src/renderer/shaders/shaders.h build/shaders_gen.o

g++ -shared -o libturtle_gl.so *.o -lglfw -lm -ldl -lpthread

rm -f *.o
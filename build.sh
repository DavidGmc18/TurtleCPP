#!/bin/bash

set -e

cd "build" || exit 1

find ../src -type f \( -name '*.cpp' \) | while read -r f; do
    # g++ -fPIC -I/usr/include/SDL2 -I/home/david/Turtle/include -c "$f" -o "$(basename "$f").o"
    g++ -fPIC $(sdl2-config --cflags) -I../include -c "$f" -o "$(basename "$f").o"
done

# g++ -shared -o libturtle.so *.o -lSDL2 -lm -ldl -lpthread
g++ -shared -o libturtle.so *.o -lSDL2_gfx $(sdl2-config --libs) -lm -ldl -lpthread

rm -f *.o
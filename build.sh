#!/bin/bash

set -e

mkdir -p build
cd "build" || exit 1

find ../src -type f \( -name '*.cpp' \) | while read -r f; do
    g++ -fPIC $(sdl2-config --cflags) -I../include -c "$f" -o "$(basename "$f").o"
done

g++ -shared -o libturtle.so *.o -lSDL2_gfx $(sdl2-config --libs) -lm -ldl -lpthread

rm -f *.o
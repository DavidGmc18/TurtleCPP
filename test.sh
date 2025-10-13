#!/bin/bash

TESTNAME=${1:-test}
BACKEND=${2:-sdl} 

cd "test" || exit 1

if [ "$BACKEND" = "gl" ]; then
    TURTLE_LIB="-lturtle_gl"
else
    TURTLE_LIB="-lturtle_sdl"
fi

g++ "$TESTNAME.cpp" -I../include -I/usr/include/SDL2 -L../build $TURTLE_LIB -lSDL2 -Wl,-rpath=../build -o "$TESTNAME.out"

"./$TESTNAME.out"
rm -f *.out
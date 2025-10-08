#!/bin/bash

TESTNAME=${1:-test}

cd "test" || exit 1

g++ "$TESTNAME.cpp" -I/home/david/Turtle/include -I/usr/include/SDL2 -L/home/david/Turtle/build -lturtle -lSDL2 -Wl,-rpath=/home/david/Turtle/build -o "$TESTNAME.out"

"./$TESTNAME.out"
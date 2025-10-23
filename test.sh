#!/bin/bash

TESTNAME=${1:-test}

cd "test" || exit 1

g++ "$TESTNAME.cpp" -I../include -I/usr/include/SDL2 -L../build -lturtle -lSDL2 -Wl,-rpath=../build -o "$TESTNAME.out"

"./$TESTNAME.out"
rm -f *.out
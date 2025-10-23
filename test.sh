#!/bin/bash

TESTNAME=${1:-test}

cd "test" || exit 1

g++ "$TESTNAME.cpp" -I../include -L../build -lturtle -Wl,-rpath=../build -o "$TESTNAME.out"

"./$TESTNAME.out"
rm -f *.out
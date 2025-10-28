#!/bin/bash

TESTNAME=${1:-test}

cd "test" || exit 1

OS_NAME=$(uname)
if [[ "$OS_NAME" == "Linux" ]]; then
    g++ "$TESTNAME.cpp" -I../include -L../build -lturtle -Wl,-rpath=../build -o "$TESTNAME.out"
elif [[ "$OS_NAME" == "Darwin" ]]; then
    clang++ "$TESTNAME.cpp" -I../include -L../build -lturtle -rpath ../build -o "$TESTNAME.out"
else
    echo "Unsupported OS"
    exit 1
fi

"./$TESTNAME.out"
rm -f *.out
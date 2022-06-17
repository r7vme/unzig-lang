#!/bin/bash
set -e
[ -d build ] || mkdir build
cmake -Bbuild
cmake --build build --parallel 16
# run tests
./build/tests
# test example
cp spec/syntax.zig build
./build/unzig build/syntax.zig

#!/bin/bash
set -e
hash peg || exit 1
hash make || exit 1

make
./build/parser_debug < syntax.zig

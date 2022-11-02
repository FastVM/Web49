#!/usr/bin/env sh
DIR="$(dirname "$1")"
emcc "$1" -o "$DIR"/$(basename -s .c "$1").wasm -s WASM=1 -s PURE_WASI=1 -s SINGLE_FILE=1 -O3
wasm2wat "$DIR"/$(basename -s .c "$1").wasm -o "$DIR"/$(basename -s .c "$1").wat

#!/usr/bin/env sh
echo emcc -s PURE_WASI=1 "$@"
emcc -s PURE_WASI=1 "$@"
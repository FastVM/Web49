#!/usr/bin/env sh
emcc -s PURE_WASI=1 "$@"
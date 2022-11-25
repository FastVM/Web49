#!/usr/bin/env sh

set -e

make -C test/bench WASM_RUN=wasm3
mv test/bench/RESULTS test/bench/results-wasm3
make -C test/bench WASM_RUN=$(pwd)/bin/miniwasm
mv test/bench/RESULTS test/bench/results-miniwasm
make -C test/bench clean
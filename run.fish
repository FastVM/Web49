#/usr/bin/env fish

emcc test/fib8.c -o test/fib8.o0.wasm -O0 -g; wasm2wat test/fib8.o0.wasm -o test/fib8.o0.wat
emcc test/fib8.c -o test/fib8.o1.wasm -O1 -g; wasm2wat test/fib8.o1.wasm -o test/fib8.o1.wat
emcc test/fib8.c -o test/fib8.o2.wasm -O2 -g; wasm2wat test/fib8.o2.wasm -o test/fib8.o2.wat
emcc test/fib8.c -o test/fib8.o3.wasm -O3 -g; wasm2wat test/fib8.o3.wasm -o test/fib8.o3.wat

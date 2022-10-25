
CLANG ?= clang

tests: test/char.wasm
	$(MAKE) -Bj --no-print-directory miniwasm.exe CC='$(CLANG)'
	miniwasm.exe test/char.wasm

test/char.wasm: test/char.c
	$(CLANG) --target=wasm32 test/char.c -o test/char.wasm --no-standard-libraries -Wl,--export-all -Wl,--no-entry

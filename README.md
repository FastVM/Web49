# Web49

Web49 contains a few tools for working with webassembly

## miniwasm

MiniWASM applies what was learned in developing MiniVM to a webassembly intepreter.

MiniVM was about 2x faster than Wasm3, with more types and more dynamism.
MiniVM was natively a register-only machine, and MiniWASM too will be mostly registers.

MiniWASM intends to support all of what people use today in webassembly, tho it is still under heavy development.

## wasm2wat

The wasm2wat tool is a faster rewrite of wabt's wasm2wat, doing only the bare minimum for now.

## wat2wasm

The wat2wasm tool is a much faster rewrite of wabt's wat2wasm, it does not handle names correctly yet.

## wasm2wasm

The wasm2wasm tool intends to do the same thing as a round trip to the text format and back. Effectivly seeing the binary as it is seen by miniwasm/wasm2wat=

# whoami

I am Shaw Summa, of MiniVM fame.

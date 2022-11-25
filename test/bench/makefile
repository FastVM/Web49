
WASM_CC ?= emcc
WASM_RUN ?= wasm3
WASM_SHELL ?= hyperfine --style=basic --runs 10 --warmup 2

OPT ?= -O3 -flto

CFLAGS ?= 
LDFLAGS ?=

SRCS := binary-trees.c fannkuch-redux.c fasta.c mandelbrot-simd.c mandelbrot.c nbody.c nop.c fib.c

WASMS := $(SRCS:%.c=%.wasm)

RESULTS := $(WASMS:%.wasm=%.txt)

PASS = Pass $(@)
FAIL = Pass $(@)
ARGS_FOR_nop := 0
ARGS_FOR_nbody := 10000000
ARGS_FOR_fannkuch-redux := 10
ARGS_FOR_mandelbrot := 2000
ARGS_FOR_mandelbrot-simd := 2000
ARGS_FOR_binary-trees := 16
ARGS_FOR_fasta := 5000000
ARGS_FOR_fib := 40
default: run

run: $(RESULTS)
	cat $(RESULTS) > RESULTS

$(RESULTS): $(WASMS) .dummy
	echo $(WASM_RUN) $(@:%.txt=%.wasm) $(ARGS_FOR_$(@:%.txt=%)) > $(@)
	$(WASM_SHELL) "$(WASM_RUN) $(@:%.txt=%.wasm) $(ARGS_FOR_$(@:%.txt=%)) > $(@:%.txt=%.out)" >>$(@)
	
$(WASMS): $(SRCS)
	$(WASM_CC) $(OPT) $(@:%.wasm=%.c) -o $(@) $(CFLAGS) $(LDFLASGS)

clean: .dummy
	rm -f $(wildcard *.out *.wasm *.txt)

.dummy:

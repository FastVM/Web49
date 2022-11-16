
EXE = .exe
EXE_RUN = 

EMCC ?= emcc
EMCC_CFLAGS = 
EMCC_OPT = -O2
INTERP = wasmer
HYPERFINE = hyperfine

OPT ?= -O2

PROG_SRCS := main/wasm2wat.c main/wat2wasm.c main/wasm2wasm.c main/miniwasm.c
PROG_OBJS := $(PROG_SRCS:%.c=%.o)

WEB49_SRCS := src/read_bin.c src/read_wat.c src/write_wat.c src/write_bin.c src/io.c src/tables.c src/interp/interp.c src/opt/tree.c src/opt/tee.c
WEB49_OBJS := $(WEB49_SRCS:%.c=%.o)

OBJS := $(WEB49_OBJS)

TEST_SRCS := test/fib35.c
TEST_TXT := $(TEST_SRCS:test/%.c=test/out.%.txt)

default: all

all: bins

bins: bin/wasm2wat$(EXE) bin/wat2wasm$(EXE) bin/wasm2wasm$(EXE) bin/miniwasm$(EXE)

test: $(TEST_TXT)

# bin

bin/miniwasm$(EXE): main/miniwasm.o $(OBJS)
	@mkdir -p bin
	$(CC) $(OPT) main/miniwasm.o $(OBJS) -o $(@) -lm $(LDFLAGS)

bin/wat2wasm$(EXE): main/wat2wasm.o $(OBJS)
	@mkdir -p bin
	$(CC) $(OPT) main/wat2wasm.o $(OBJS) -o $(@) -lm $(LDFLAGS)

bin/wasm2wat$(EXE): main/wasm2wat.o $(OBJS)
	@mkdir -p bin
	$(CC) $(OPT) main/wasm2wat.o $(OBJS) -o $(@) -lm $(LDFLAGS)

bin/wasm2wasm$(EXE): main/wasm2wasm.o $(OBJS)
	@mkdir -p bin
	$(CC) $(OPT) main/wasm2wasm.o $(OBJS) -o $(@) -lm $(LDFLAGS)

# util

format: .dummy
	find . -name '*.c' | xargs -I FILENAME clang-format -style=file -i FILENAME
	find . -name '*.h' | xargs -I FILENAME clang-format -style=file -i FILENAME

# intermediate files

$(PROG_OBJS) $(WEB49_OBJS): $(@:%.o=%.c)
	$(CC) -c $(OPT) $(@:%.o=%.c) -o $(@) $(CFLAGS) -D_CRT_SECURE_NO_WARNINGS

# dummy

.dummy:


EXE = .exe

OPT ?= -O2

PROG_SRCS := main/wasm2wat.c main/wat2wasm.c main/wasm2wasm.c
PROG_OBJS := $(PROG_SRCS:%.c=%.o)

WEB49_SRCS := src/read_bin.c src/read_wat.c src/write_wat.c src/write_bin.c
WEB49_OBJS := $(WEB49_SRCS:%.c=%.o)

OBJS := $(WEB49_OBJS)

default: all

all: bin/wasm2wat$(EXE) bin/wat2wasm$(EXE) bin/wasm2wasm$(EXE)

format: .dummy
	find . -name '*.c' | xargs -I FILENAME clang-format -style=file -i FILENAME
	find . -name '*.h' | xargs -I FILENAME clang-format -style=file -i FILENAME

bin/wat2wasm$(EXE): main/wat2wasm.o $(OBJS)
	@mkdir -p bin
	$(CC) $(OPT) main/wat2wasm.o $(OBJS) -o $(@) $(LDFLAGS)

bin/wasm2wat$(EXE): main/wasm2wat.o $(OBJS)
	@mkdir -p bin
	$(CC) $(OPT) main/wasm2wat.o $(OBJS) -o $(@) $(LDFLAGS)

bin/wasm2wasm$(EXE): main/wasm2wasm.o $(OBJS)
	@mkdir -p bin
	$(CC) $(OPT) main/wasm2wasm.o $(OBJS) -o $(@) $(LDFLAGS)

# clean

clean: gcc-pgo-clean clang-pgo-clean objs-clean

# intermediate files

$(PROG_OBJS) $(WEB49_OBJS): $(@:%.o=%.c)
	$(CC) -c $(OPT) $(@:%.o=%.c) -o $(@) $(CFLAGS) -D_CRT_SECURE_NO_WARNINGS

# dummy

.dummy:

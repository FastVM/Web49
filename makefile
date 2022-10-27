
EXE = .exe

OPT ?= -O2

PROG_SRCS := main/wasm2wat.c
PROG_OBJS := $(PROG_SRCS:%.c=%.o)

WEB49_SRCS := src/read_bin.c src/write_wat.c
WEB49_OBJS := $(WEB49_SRCS:%.c=%.o)

OBJS := $(WEB49_OBJS)

default: all

all: bin/wasm2wat$(EXE)

format: .dummy
	find . -name '*.c' | xargs -I FILENAME clang-format -style=file -i FILENAME
	find . -name '*.h' | xargs -I FILENAME clang-format -style=file -i FILENAME

bin/wasm2wat$(EXE): main/wasm2wat.o $(OBJS)
	@mkdir -p bin
	$(CC) $(OPT) main/wasm2wat.o $(OBJS) -o $(@) $(LDFLAGS)

# clean

clean: gcc-pgo-clean clang-pgo-clean objs-clean

# intermediate files

$(PROG_OBJS) $(WEB49_OBJS): $(@:%.o=%.c)
	$(CC) -c $(OPT) $(@:%.o=%.c) -o $(@) $(CFLAGS) -D_CRT_SECURE_NO_WARNINGS

# dummy

.dummy:

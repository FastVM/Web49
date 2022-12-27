
PYTHON ?= python3
OPT ?= -O2

PROG_SRCS := main/wasm2wat.c main/wat2wasm.c main/wasm2wasm.c main/miniwasm.c main/raywasm.c main/runtime/rlruntime.c
PROG_OBJS := $(PROG_SRCS:%.c=%.o)

WEB49_SRCS := src/read_bin.c src/read_wat.c src/write_wat.c src/write_bin.c src/io.c src/tables.c src/interp/interp.c src/opt/tree.c src/opt/tee.c src/ast.c src/api/wasi.c
WEB49_OBJS := $(WEB49_SRCS:%.c=%.o)

OBJS := $(WEB49_OBJS)

RAYLIB_SRCS := src/api/raylib.c raylib/src/raudio.c raylib/src/rcore.c raylib/src/rmodels.c raylib/src/rshapes.c raylib/src/rtext.c raylib/src/rtextures.c raylib/src/utils.c
RAYLIB_OBJS := $(RAYLIB_SRCS:%.c=%.o)

LDFLAGS_GL_FreeBSD = -lGL
LDFLAGS_GL_Linux = -lGL -lglfw
LDFLAGS_GL_Darwin = -framework OpenGL -lglfw

UNAME_S != uname -s

default: all

all: bins

bins: bin/wasm2wat$(EXE) bin/wat2wasm$(EXE) bin/wasm2wasm$(EXE) bin/miniwasm$(EXE)

# raylib

src/api/raylib.c: src/api/raylib.py src/api/raylib.json
	$(PYTHON) src/api/raylib.py

bin/raywasm$(EXE): main/raywasm.o $(OBJS) $(RAYLIB_OBJS)
	@mkdir -p bin
	$(CC) $(OPT) main/raywasm.o $(RAYLIB_OBJS) -L/usr/local/lib $(OBJS) -o $(@) -lm -pthread -ldl $(LDFLAGS_GL_$(UNAME_S)) $(LDFLAGS)

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
	find . -name '*.inc' | xargs -I FILENAME clang-format -style=file -i FILENAME

clean: .dummy
	find . -name '*.o' | xargs rm
	find bin -type f | xargs rm

# intermediate files

$(RAYLIB_OBJS): $(@:%.o=%.c)
	$(CC) -c $(OPT) $(@:%.o=%.c) -o $(@) -w -DPLATFORM_DESKTOP -Iraylib/include -I/usr/local/include $(CFLAGS)

$(PROG_OBJS) $(WEB49_OBJS): $(@:%.o=%.c)
	$(CC) -c $(OPT) $(@:%.o=%.c) -o $(@) $(CFLAGS)

# dummy

.dummy:

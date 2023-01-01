
WAIT ?= 1s

PYTHON ?= python3
OPT ?= -O2

INSTALL ?= /usr/local/bin

EMCC ?= emcc

PROG_SRCS := main/wasm2wat.c main/wat2wasm.c main/wasm2wasm.c main/miniwasm.c main/raywasm.c main/runtime/rlruntime.c
PROG_OBJS := $(PROG_SRCS:%.c=%.o)

WEB49_SRCS := src/read_bin.c src/read_wat.c src/write_wat.c src/write_bin.c src/io.c src/tables.c src/interp/interp.c src/opt/tree.c src/opt/tee.c src/ast.c src/api/wasi.c
WEB49_OBJS := $(WEB49_SRCS:%.c=%.o)

OBJS := $(WEB49_OBJS)

RAYLIB_SRCS := src/api/raylib.c raylib/src/raudio.c raylib/src/rcore.c raylib/src/rmodels.c raylib/src/rshapes.c raylib/src/rtext.c raylib/src/rtextures.c raylib/src/utils.c
RAYLIB_OBJS := $(RAYLIB_SRCS:%.c=%.o)

LDFLAGS_GL_FreeBSD = -lGL -lglfw
LDFLAGS_GL_Linux = -lGL -lglfw
LDFLAGS_GL_Darwin = -framework OpenGL -lglfw

UNAME_S_CMD != uname -s

UNAME_S ?= $(UNAME_S_CMD)

TEST_NAMES = address align binary-leb128 binary block br br_if br_table bulk call call_indirect comments const conversions custom data elem endianness exports f32 f32_bitwise f32_cmp f64 f64_bitwise f64_cmp fac float_exprs float_literals float_memory float_misc forward func func_ptrs global i32 i64 if imports inline-module int_exprs int_literals labels left-to-right linking load local_get local_set local_tee loop memory memory_copy memory_fill memory_grow memory_init memory_redundancy memory_size memory_trap names nop ref_func ref_is_null ref_null return select skip-stack-guard-page stack start store switch table-sub table table_copy table_fill table_get table_grow table_init table_set table_size token tokens traps type unreachable unreached-invalid unreached-valid unwind utf8-custom-section-id utf8-import-field utf8-import-module utf8-invalid-encoding

TEST_PREFIX = test/core

TEST_FILES = $(TEST_NAMES:%=$(TEST_PREFIX)/%.wast)
TEST_OUTPUTS = $(TEST_NAMES:%=$(TEST_PREFIX)/%.txt)

default: all

all: bins

# install web49

install: bins bin/raywasm raylib/lib raylib/lib
	cp -r bin/raywasm bin/miniwasm web49 emraylib raylib $(INSTALL)
	chmod +x $(INSTALL)/raywasm $(INSTALL)/miniwasm $(INSTALL)/web49 $(INSTALL)/emraylib

raylib/lib: raylib/src
	mkdir -p lib
	$(EMCC) -Iraylib/include -O2 -c raylib/src/raudio.c -o raylib/lib/raudio.o
	$(EMCC) -Iraylib/include -O2 -c raylib/src/rmodels.c -o raylib/lib/rmodels.o
	$(EMCC) -Iraylib/include -O2 -c raylib/src/rshapes.c -o raylib/lib/rshapes.o
	$(EMCC) -Iraylib/include -O2 -c raylib/src/rtext.c -o raylib/lib/rtext.o
	$(EMCC) -Iraylib/include -O2 -c raylib/src/rtextures.c -o raylib/lib/rtextures.o
	$(EMCC) -Iraylib/include -O2 -c raylib/src/utils.c -o raylib/lib/utils.o

# tests

test: $(TEST_OUTPUTS)
	@cat $(TEST_OUTPUTS) | sort > results.txt

$(TEST_OUTPUTS): bin/miniwasm $(@:%.txt=%.wast)
	@cp bin/miniwasm $(@:$(TEST_PREFIX)/%.txt=./bin/%)
	@timeout $(WAIT) $(@:$(TEST_PREFIX)/%.txt=./bin/%) $(@:%.txt=%.wast) 2>/dev/null; \
		if test $$? -eq 0; \
		then echo "PASS $(@:$(TEST_PREFIX)/%.txt=%)" > $(@); \
		else echo "FAIL $(@:$(TEST_PREFIX)/%.txt=%)" > $(@); \
		fi

# raylib

src/api/raylib.c: src/api/raylib.py src/api/raylib.json
	$(PYTHON) src/api/raylib.py

bin/raywasm: main/raywasm.o $(OBJS) $(RAYLIB_OBJS)
	@mkdir -p bin
	$(CC) $(OPT) main/raywasm.o $(RAYLIB_OBJS) -L/usr/local/lib $(OBJS) -o $(@) -lm -pthread -ldl $(LDFLAGS_GL_$(UNAME_S)) $(LDFLAGS)

# bin

bins: bin/wasm2wat bin/wat2wasm bin/wasm2wasm bin/miniwasm

bin/miniwasm: main/miniwasm.o $(OBJS)
	@mkdir -p bin
	$(CC) $(OPT) main/miniwasm.o $(OBJS) -o $(@) -lm $(LDFLAGS)

bin/wat2wasm: main/wat2wasm.o $(OBJS)
	@mkdir -p bin
	$(CC) $(OPT) main/wat2wasm.o $(OBJS) -o $(@) -lm $(LDFLAGS)

bin/wasm2wat: main/wasm2wat.o $(OBJS)
	@mkdir -p bin
	$(CC) $(OPT) main/wasm2wat.o $(OBJS) -o $(@) -lm $(LDFLAGS)

bin/wasm2wasm: main/wasm2wasm.o $(OBJS)
	@mkdir -p bin
	$(CC) $(OPT) main/wasm2wasm.o $(OBJS) -o $(@) -lm $(LDFLAGS)

# util

format: .dummy
	find . -name '*.c' | xargs -I FILENAME clang-format -style=file -i FILENAME
	find . -name '*.h' | xargs -I FILENAME clang-format -style=file -i FILENAME
	find . -name '*.inc' | xargs -I FILENAME clang-format -style=file -i FILENAME

clean: .dummy
	find src main raylib/src -name '*.o' | xargs rm
	find bin -type f | xargs rm
	find test/core -name '*.txt' | xargs rm

# intermediate files

$(RAYLIB_OBJS): $(@:%.o=%.c)
	$(CC) -c $(OPT) $(@:%.o=%.c) -o $(@) -w -DPLATFORM_DESKTOP -Iraylib/include -I/usr/local/include $(CFLAGS)

$(PROG_OBJS) $(WEB49_OBJS): $(@:%.o=%.c)
	$(CC) -c $(OPT) $(@:%.o=%.c) -o $(@) $(CFLAGS)

# dummy

.dummy:

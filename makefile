
PYTHON ?= python3
OPT ?= -O2

INSTALL ?= install

EMCC ?= emcc

PROG_SRCS := main/wat2wat.c main/wasm2wat.c main/wat2wasm.c main/wasm2wasm.c main/miniwasm.c main/raywasm.c main/runtime/rlruntime.c
PROG_OBJS := $(PROG_SRCS:%.c=%.o)

WEB49_SRCS := src/lib.c src/read_bin.c src/read_wat.c src/write_wat.c src/write_bin.c src/io.c src/tables.c src/interp/interp.c src/opt/tree.c src/opt/tee.c src/ast.c src/api/wasi.c
WEB49_OBJS := $(WEB49_SRCS:%.c=%.o)

OBJS := $(WEB49_OBJS)

UNAME_S_CMD != uname -s

UNAME_S ?= $(UNAME_S_CMD)

RGLFW_M_OR_C_Windows = c
RGLFW_M_OR_C_FreeBSD = c
RGLFW_M_OR_C_Linux = c
RGLFW_M_OR_C_Darwin = m

TEST_PREFIX = test/core

TEST_FILES != find $(TEST_PREFIX) -name '*.wast'
TEST_OUTPUTS = $(TEST_FILES:%.wast=%.txt)

default: all

all: bins

# install web49

install: bins
	cp bin/miniwasm $(INSTALL)
	chmod $(INSTALL)/miniwasm

# tests

test: results.txt

results.txt: $(TEST_OUTPUTS)
	@cat /dev/null $(TEST_OUTPUTS) | sort > results.txt

$(TEST_OUTPUTS): bin/miniwasm $(@:%.txt=%.wast) | $(TEST_PREFIX)
	@./bin/miniwasm $(@:%.txt=%.wast) 2>$(@:%.txt=%.log); \
		if test $$? -eq 0; \
		then mv $(@:%.txt=%.log) $(@:%.txt=%.pass.log) && echo "PASS $(@:$(TEST_PREFIX)/%.txt=%)" > $(@); \
		else mv $(@:%.txt=%.log) $(@:%.txt=%.fail.log) && echo "FAIL $(@:$(TEST_PREFIX)/%.txt=%)" > $(@); \
		fi

# test/wasi:
# 	test -d wasi-testsuite || git clone https://github.com/WebAssembly/wasi-testsuite spec --depth 1
# 	rm -fr test/wasi 

test/core:
	test -d spec || git clone https://github.com/WebAssembly/spec/ spec --depth 1
	rm -fr test/core
	cp -r spec/test/core test/core
	rm -r test/core/simd/meta

# bin

bins: bin/wasm2wat bin/wat2wasm bin/wasm2wasm bin/wat2wat bin/miniwasm

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

bin/wat2wat: main/wat2wat.o $(OBJS)
	@mkdir -p bin
	$(CC) $(OPT) main/wat2wat.o $(OBJS) -o $(@) -lm $(LDFLAGS)

# util

format: .dummy
	find src main -name '*.c' | xargs -I FILENAME clang-format -style=file -i FILENAME
	find src main -name '*.h' | xargs -I FILENAME clang-format -style=file -i FILENAME
	find src main -name '*.inc' | xargs -I FILENAME clang-format -style=file -i FILENAME

clean: .dummy
	find src main -name '*.o' | xargs rm
	find bin -type f | xargs rm
	find test/core -name '*.txt' | xargs rm
	find test/core -name '*.log' | xargs rm

# intermediate files

$(PROG_OBJS) $(WEB49_OBJS): $(@:%.o=%.c)
	$(CC) -c $(OPT) $(@:%.o=%.c) -o $(@) $(CFLAGS)

# dummy

.dummy:

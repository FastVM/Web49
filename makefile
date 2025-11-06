
MODE ?= opt

BUILD_DIR = ./build/$(MODE)/
BIN_DIR = $(BUILD_DIR)bin/
OBJ_DIR = $(BUILD_DIR)obj/
TEST_DIR = $(BUILD_DIR)test/

PYTHON ?= python3

PROG_SRCS := main/wat2wat.c main/wasm2wat.c main/wat2wasm.c main/wasm2wasm.c main/miniwasm.c main/raywasm.c main/runtime/rlruntime.c
PROG_OBJS := $(PROG_SRCS:%.c=$(OBJ_DIR)%.o)

WEB49_SRCS := src/lib.c src/read_bin.c src/read_wat.c src/write_wat.c src/write_bin.c src/io.c src/tables.c src/interp/interp.c src/opt/tree.c src/opt/tee.c src/ast.c src/wasi/wasi.c
WEB49_OBJS := $(WEB49_SRCS:%.c=$(OBJ_DIR)%.o)

OBJS := $(WEB49_OBJS)

TEST_PREFIX = test/core

TEST_FILES != find $(TEST_PREFIX) -name '*.wast'
TEST_OUTPUTS = $(TEST_FILES:%.wast=%.txt)

# modes
FLAGS_san = -g3 -ggdb -fsanitize=address,undefined
FLAGS_debug = -g3 -ggdb

CLAGS_opt = -O3
LDFLAGS_opt = -flto

CFLAGS += $(CFLAGS_$(MODE)) $(FLAGS_$(MODE))
LDFLAGS += $(LDFLAGS_$(MODE)) $(FLAGS_$(MODE))

default: all

all: bins test

# tests

TESTS != find test -type f -name '*.wast'
TEST_LOGS = $(TESTS:%.wast=$(TEST_DIR)log/%.log)
TEST_RESULT = $(TEST_DIR)result

test: $(TEST_RESULT)

$(TEST_RESULT): $(TEST_LOGS)
	@echo -n > $(TEST_RESULT).pass
	@echo -n > $(TEST_RESULT).fail
	@sort -u $(TEST_RESULT).pass -o $(TEST_RESULT).pass
	@sort -u $(TEST_RESULT).fail -o $(TEST_RESULT).fail
	@cat $(TEST_RESULT).pass > $(TEST_RESULT)
	@echo >> $(TEST_RESULT)
	@cat $(TEST_RESULT).fail >> $(TEST_RESULT)
	@rm $(TEST_RESULT).pass $(TEST_RESULT).fail

$(TEST_DIR)log/%.log: %.wast $(BIN_DIR)miniwasm
	@mkdir -p $(dir $(@))
	@echo $(BIN_DIR)miniwasm $(<); if $(BIN_DIR)miniwasm $(<) 2>$(@); then echo pass $(<) >> $(TEST_RESULT).pass; else echo fail $(<) >> $(TEST_RESULT).fail; fi

# bin

MAINS != find main -type f -name '*.c'
MAIN_BINS = $(MAINS:main/%.c=$(BIN_DIR)%)

bins: $(MAIN_BINS)

$(BIN_DIR)%: $(OBJ_DIR)main/%.o $(OBJS)
	@mkdir -p $(dir $(@))
	$(CC) $(^) -o $(@) -lm $(LDFLAGS)

# intermediate files

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $(@))
	$(CC) -c $(OPT) $(<) -o $(@) $(CFLAGS)

# util

.PHONY: format
format: .dummy
	find src main -name '*.c' | xargs -I FILENAME clang-format -style=file -i FILENAME
	find src main -name '*.h' | xargs -I FILENAME clang-format -style=file -i FILENAME
	find src main -name '*.inc' | xargs -I FILENAME clang-format -style=file -i FILENAME

.PHONY: clean
clean: .dummy
	rm -rf build

.dummy:

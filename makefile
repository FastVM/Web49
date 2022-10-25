
OPT ?= -O2

PROG_SRCS := src/main.c
PROG_OBJS := $(PROG_SRCS:%.c=%.o)

VM_SRCS := src/parse.c src/wat.c
VM_OBJS := $(VM_SRCS:%.c=%.o)

OBJS := $(VM_OBJS)

default: all

all: miniwasm.exe

format: .dummy
	find . -name '*.c' | xargs -I FILENAME clang-format -style=file -i FILENAME
	find . -name '*.h' | xargs -I FILENAME clang-format -style=file -i FILENAME

miniwasm.exe: src/main.o $(OBJS)
	@mkdir -p bin
	$(CC) $(OPT) src/main.o $(OBJS) -o $(@) $(LDFLAGS)

miniwasm.wasm: src/main.o $(OBJS)
	@mkdir -p bin
	$(CC) $(OPT) src/main.o $(OBJS) -o $(@) $(LDFLAGS)

# clean

clean: gcc-pgo-clean clang-pgo-clean objs-clean

# intermediate files

$(PROG_OBJS) $(VM_OBJS): $(@:%.o=%.c)
	$(CC) -c $(OPT) $(@:%.o=%.c) -o $(@) $(CFLAGS) -D_CRT_SECURE_NO_WARNINGS

# dummy

.dummy:

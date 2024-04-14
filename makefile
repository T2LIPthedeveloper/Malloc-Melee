# Default goal
.DEFAULT_GOAL := all

# Compiler for Linux, macOS, and Unix
CC := gcc

# Compiler for Windows (MinGW)
CC_WIN := x86_64-w64-mingw32-gcc

# Flags
CFLAGS := -Wall -Wextra -g

# Output directory
OUT_DIR := .

# Target executable names
TARGET_LINUX := MALLOC_MELEE
TARGET_WIN := MALLOC_MELEE.exe

# Source files
SRC := $(wildcard *.c)
SRC += $(wildcard engine/*.c)
SRC += $(wildcard locations/*/*.c)

# Object files
OBJ := $(SRC:.c=.o)

# Determine OS and set compiler and target
ifeq ($(OS),Windows_NT)
    # Windows
    CC := $(CC_WIN)
    TARGET := $(TARGET_WIN)
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        # Linux
        TARGET := $(TARGET_LINUX)
    endif
    ifeq ($(UNAME_S),Darwin)
        # macOS
        TARGET := $(TARGET_LINUX)
    endif
endif

# Build rule for all platforms
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(OUT_DIR)/$@

# Rule for compiling source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove all generated files
clean:
	rm -rf $(OBJ) $(TARGET_LINUX) $(TARGET_WIN)

# Rule for building on Windows
windows:
	$(MAKE) all OS=Windows_NT

# Rule for building on Linux, macOS, Unix
linux:
	$(MAKE) all OS=Linux

.PHONY: all clean windows linux

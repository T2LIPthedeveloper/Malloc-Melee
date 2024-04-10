# Compiler for Linux, macOS, and Unix-like systems
CC := gcc

# Compiler for Windows (MinGW)
CC_WIN := x86_64-w64-mingw32-gcc

# Flags
CFLAGS := -Wall -Wextra -g

# Output directory
OUT_DIR := distributions

# Target executable names
TARGET := MALLOC_MELEE
TARGET_WIN := $(addsuffix .exe,$(TARGET))

# Source files
SRC := $(wildcard *.c)
SRC += $(wildcard engine/*.c)
SRC += $(wildcard locations/*/*.c)

# Object files (not used in this version)
# OBJ := $(SRC:.c=.o)

# Determine OS and set compiler and target executable
ifeq ($(OS),Windows_NT)
    # Windows
    CC := $(CC_WIN)
    TARGET := $(OUT_DIR)/$(TARGET_WIN)
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        # Linux
        TARGET := $(OUT_DIR)/$(TARGET)
    endif
    ifeq ($(UNAME_S),Darwin)
        # macOS
        TARGET := $(OUT_DIR)/$(TARGET)
    endif
endif

# Build rule for both Linux and Windows
all: $(OUT_DIR) $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

# Rule for creating output directory
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Clean rule to remove all build artifacts
clean:
	rm -rf $(OUT_DIR)

# Rule for building on Windows
windows: clean
	$(MAKE) all OS=Windows_NT

# Rule for building on Linux, macOS, Unix
linux: clean
	$(MAKE) all OS=Linux

.PHONY: all clean windows linux

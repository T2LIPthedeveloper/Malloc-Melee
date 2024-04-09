# Default goal
.DEFAULT_GOAL := build

# Compiler
CC := gcc

# Flags
CFLAGS := -Wall -Wextra -g

# Output directory
OUT_DIR := bin

# Target executable name
TARGET := MALLOC_MELEE

# Source files
SRC := $(wildcard *.c)
SRC += $(wildcard engine/*.c)
SRC += $(wildcard locations/*/*.c)

# Object files
OBJ := $(SRC:.c=.o)

# Determine OS
ifeq ($(OS),Windows_NT)
    # Windows
    TARGET := $(addsuffix .exe,$(TARGET))
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        # Linux
        TARGET := $(addprefix $(OUT_DIR)/,$(TARGET))
    endif
    ifeq ($(UNAME_S),Darwin)
        # macOS
        TARGET := $(addprefix $(OUT_DIR)/,$(TARGET))
    endif
endif

# Build rule
build: $(OUT_DIR) $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Rule for compiling source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for creating output directory
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Clean rule
clean:
	rm -rf $(OUT_DIR) $(OBJ) $(TARGET)

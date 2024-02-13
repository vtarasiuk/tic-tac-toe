# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror -Wpedantic

# Source files
SRCS = main.c output.c game.c

# Object files directory
BUILD_DIR = ./build

# Object files
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))

# Executable directory
BIN_DIR = ./bin

# Executable
TARGET = $(BIN_DIR)/main

# Default target
all: $(TARGET)

# Create build and bin directories if they don't exist
$(shell mkdir -p $(BUILD_DIR) $(BIN_DIR))

# Linking
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compilation
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

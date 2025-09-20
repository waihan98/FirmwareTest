# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude -g

# Project name (output executable)
TARGET = q3

# Source file
SRC = src/main.c

# Default rule
all: $(TARGET)

# Build the program
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Clean build files
clean:
	rm -f $(TARGET)

# Run program
run: $(TARGET)
	./$(TARGET)

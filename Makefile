# Compiler settings
CC = gcc
CFLAGS = -Wall -Iinclude -g

# Target executable
TARGET = compiler

# Source and object files
SRCS = src/main.c src/tokenizer.c src/parser.c src/executor.c src/isInDictionary.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Pattern rule for compiling source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# PHONY targets to prevent conflicts with files named "clean" or "all"
.PHONY: all clean

# Compiler settings
CC = gcc
CFLAGS = -Wall -Iinclude

# Target executable
TARGET = compiler

# Source files
SRCS = src/main.c src/tokenizer.c src/parser.c src/executor.c src/isInDictionary.c

# Object files
OBJS = $(SRCS:.c=.o)

# Build rules
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

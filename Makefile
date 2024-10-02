CC = gcc

CFLAGS = -Wall -Iinc

SRCS = src/main.c src/chunk.c src/memory.c src/debug.c src/value.c
OBJS = $(SRCS:.c=.o)

TARGET = clox

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) -o $@ $^

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

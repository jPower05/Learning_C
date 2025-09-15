# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Collect all .c files in the current directory
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

# Name of the output binary (can be overridden: make TARGET=myprog)
TARGET ?= program

# Default rule
all: $(TARGET)

# Link object files into final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

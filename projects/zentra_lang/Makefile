# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -g -fsanitize=address

# Homebrew (ARM Mac) CUnit include and lib paths
CUNIT_INC = /opt/homebrew/include
CUNIT_LIB = /opt/homebrew/lib

# Directories
SRC_DIR := src
TEST_DIR := test

# Sources and objects
SRC_SRCS := $(wildcard $(SRC_DIR)/*.c)
SRC_OBJS := $(SRC_SRCS:.c=.o)

TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c, $(TEST_DIR)/%.o, $(TEST_SRCS))

# Output binaries
TARGET ?= program
TEST_TARGET ?= test_runner

# Default target
all: $(TARGET)

# Build main program
$(TARGET): $(SRC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Build and run unit tests
test: $(SRC_OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) -I$(CUNIT_INC) -L$(CUNIT_LIB) -o $(TEST_TARGET) $^ -lcunit
	./$(TEST_TARGET)

# Compile src .c files to .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

# Compile test .c files to .o
$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -I$(SRC_DIR) -I$(CUNIT_INC) -c $< -o $@

# Clean up all build artifacts
clean:
	rm -f $(SRC_DIR)/*.o
	rm -f $(TEST_DIR)/*.o
	rm -f $(TARGET) $(TEST_TARGET)

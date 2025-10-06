# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -g

# CUnit paths (adjust if installed somewhere else)
CUNIT_INC = /usr/local/include
CUNIT_LIB = /usr/local/lib

# Directories
SRC_DIR := src
TEST_DIR := test

# Source files
SRC_SRCS := $(wildcard $(SRC_DIR)/*.c)
SRC_OBJS := $(SRC_SRCS:.c=.o)

TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c, $(TEST_DIR)/%.o, $(TEST_SRCS))

# Output binaries
TARGET ?= program
TEST_TARGET ?= test_runner

# Default target
all: test

# Build main program (optional)
$(TARGET): $(SRC_OBJS)
	@echo "[Building main program...]"
	$(CC) $(CFLAGS) -o $@ $^

# Build and run tests
test: $(TEST_TARGET)

$(TEST_TARGET): $(SRC_OBJS) $(TEST_OBJS)
	@echo "[Building test runner...]"
	$(CC) $(CFLAGS) -I$(SRC_DIR) -I$(CUNIT_INC) -L$(CUNIT_LIB) -o $(TEST_TARGET) $^ -lcunit
	@echo "[Running tests...]"
	./$(TEST_TARGET)

# Compile src files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "[Compiling $<...]"
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

# Compile test files
$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	@echo "[Compiling test $<...]"
	$(CC) $(CFLAGS) -I$(SRC_DIR) -I$(CUNIT_INC) -c $< -o $@

# Clean build artifacts
clean:
	@echo "[Cleaning up...]"
	rm -f $(SRC_DIR)/*.o
	rm -f $(TEST_DIR)/*.o
	rm -f $(TARGET) $(TEST_TARGET)

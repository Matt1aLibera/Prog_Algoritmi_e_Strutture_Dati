# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = 

# Directories
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Source files
MAIN_SRC = $(SRC_DIR)/main_ex1.c
SORTING_SRC = $(SRC_DIR)/sorting_algorithms.c
TEST_SRC = $(SRC_DIR)/test_ex1.c

# Object files
MAIN_OBJ = $(OBJ_DIR)/main_ex1.o
SORTING_OBJ = $(OBJ_DIR)/sorting_algorithms.o
TEST_OBJ = $(OBJ_DIR)/test_ex1.o

# Executables
MAIN_EXEC = $(BIN_DIR)/main_ex1
TEST_EXEC = $(BIN_DIR)/test_ex1

# Default target
all: $(MAIN_EXEC) $(TEST_EXEC)

# Create directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Main executable
$(MAIN_EXEC): $(MAIN_OBJ) $(SORTING_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Test executable  
$(TEST_EXEC): $(TEST_OBJ) $(SORTING_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Object files
$(OBJ_DIR)/main_ex1.o: $(MAIN_SRC) $(SRC_DIR)/main_ex1.h $(SRC_DIR)/sorting_algorithms.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $(MAIN_SRC)

$(OBJ_DIR)/sorting_algorithms.o: $(SORTING_SRC) $(SRC_DIR)/sorting_algorithms.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $(SORTING_SRC)

$(OBJ_DIR)/test_ex1.o: $(TEST_SRC) $(SRC_DIR)/test_ex1.h $(SRC_DIR)/sorting_algorithms.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $(TEST_SRC)

# Clean target
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run tests
test: $(TEST_EXEC)
	@echo "🚀 Running tests..."
	./$(TEST_EXEC)

# Phony targets
.PHONY: all clean test
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = 

# Directories
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Source files
MAIN_SRC = $(SRC_DIR)/main_ex2.c
EDIT_DISTANCE_SRC = $(SRC_DIR)/edit_distance.c
TEST_SRC = $(SRC_DIR)/test_ex2.c

# Object files
MAIN_OBJ = $(OBJ_DIR)/main_ex2.o
EDIT_DISTANCE_OBJ = $(OBJ_DIR)/edit_distance.o
TEST_OBJ = $(OBJ_DIR)/test_ex2.o

# Executables
MAIN_EXEC = $(BIN_DIR)/main_ex2
TEST_EXEC = $(BIN_DIR)/test_ex2

# Default target
all: $(MAIN_EXEC) $(TEST_EXEC)

# Create directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Main executable
$(MAIN_EXEC): $(MAIN_OBJ) $(EDIT_DISTANCE_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Test executable  
$(TEST_EXEC): $(TEST_OBJ) $(EDIT_DISTANCE_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Object files
$(OBJ_DIR)/main_ex2.o: $(MAIN_SRC) $(SRC_DIR)/edit_distance.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $(MAIN_SRC)

$(OBJ_DIR)/edit_distance.o: $(EDIT_DISTANCE_SRC) $(SRC_DIR)/edit_distance.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $(EDIT_DISTANCE_SRC)

$(OBJ_DIR)/test_ex2.o: $(TEST_SRC) $(SRC_DIR)/edit_distance.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $(TEST_SRC)

# Clean target
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run tests
test: $(TEST_EXEC)
	@echo "🚀 Running tests..."
	./$(TEST_EXEC)
	
# Run main
run: $(MAIN_EXEC)
	@echo "🚀 Running main..."
	./$(MAIN_EXEC)

# Phony targets
.PHONY: all clean test run
# --- Setup ---
CC      := gcc
CFLAGS  := -Wall -Wextra -Iinclude

# --- Project Structure ---
SRC_DIR  := src
OBJ_DIR  := obj
BIN      := connect4

# --- OS Detection ---
ifeq ($(OS),Windows_NT)
    CLEAN_CMD = if exist $(OBJ_DIR) rd /s /q $(OBJ_DIR) & if exist $(BIN).exe del /q $(BIN).exe*
else
    CLEAN_CMD = if exist $(OBJ_DIR) rm -rf $(OBJ_DIR) & if exist $(BIN) rm -f $(BIN)
endif

# --- File Discovery ---
# Finds all .c files in src/
SRCS := $(wildcard $(SRC_DIR)/*.c)
# Replaces 'src/*.c' with 'obj/*.o' for the object files
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default target: builds the game
all: clean $(BIN)

# Link: Combines all .o files into the final executable
$(BIN): $(OBJS)
	@echo "Linking points into: $(BIN)"
	$(CC) $(OBJS) -o $(BIN)

# Compile: Turns each .c file into a .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling: $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Create objs directory
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

# Clean: Removes compiled files to start fresh
clean:
	@echo "Cleaning up..."
	@$(CLEAN_CMD)

# Rebuild: Cleans and then builds
rebuild: clean all

.PHONY: all clean rebuild
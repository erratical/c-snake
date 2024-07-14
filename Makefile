# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -c

# Current directory
CURRENT_DIR = .

# Other directories at the same level
OTHER_DIRS = $(wildcard */)

# Source files
SOURCES = $(wildcard $(CURRENT_DIR)/*.c)
SOURCES += $(foreach dir, $(OTHER_DIRS), $(wildcard $(dir)*.c))

# Object files
OBJ_DIR = _obj
OBJECTS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SOURCES)))

# Executable name
EXECUTABLE = snake

# Default target
all: $(OBJ_DIR) $(EXECUTABLE)

# Create obj directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Linking object files
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

# Compiling source files
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: */%.c
	$(CC) $(CFLAGS) $< -o $@

# Clean target
clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE)

# Clean and clear
cleanr: clean
	clear

run:
	./$(EXECUTABLE)

# Phony targets (always executed)
.PHONY: all clean cleanr run
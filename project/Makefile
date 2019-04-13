# The C compiler
CC = gcc
# Global compiler arguments
CFLAGS = -c -I ../include -Wall -Wextra
# Global linker arguments
LDFLAGS =

# Source directory
SRC_DIR = ../src
# Build directory
BUILD_DIR = ../build
# Binary directory
BIN_DIR = ../bin
# Name of the binaries
PROGRAM = memhack

# List of source files, SRC_DIR is the root path
SOURCES = memhack.c error.c arch/linux/memhack_linux.c
OBJECTS = $(SOURCES:%.c=$(BUILD_DIR)/%.o)

.PHONY: all
all: $(BIN_DIR)/static/$(PROGRAM).a

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*

# Empty rule to stop make from looking for a Makefile to build
.PHONY: Makefile
Makefile: ;

$(BIN_DIR)/static/$(PROGRAM).a: $(OBJECTS)
	@mkdir -p $(BIN_DIR)/static
	ar csr $@ $(OBJECTS)

# Build the object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(strip $(CC) $(CFLAGS) -o $@ $<)


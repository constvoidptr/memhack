# The C compiler
CC = gcc
# Global compiler arguments
CFLAGS = -c -I ../include -Wall -Wextra
# Global linker arguments
LDFLAGS =
# Dependency generation arguments
DEPFLAGS = -MM -MT $(@:%.d=%.o) -I ../include

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
DEPENDENCIES = $(OBJECTS:%.o=%.d)

.PHONY: all
all: static dynamic

.PHONY: static
static: $(BIN_DIR)/static/$(PROGRAM).a

.PHONY: dynamic
dynamic: $(BIN_DIR)/dynamic/$(PROGRAM).so

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*

# Empty rule to stop make from looking for a Makefile to build
.PHONY: Makefile
Makefile: ;

# Build the library statically
$(BIN_DIR)/static/$(PROGRAM).a: $(OBJECTS)
	@mkdir -p $(BIN_DIR)/static
	ar csr $@ $(OBJECTS)

# Build the library dynamically
$(BIN_DIR)/dynamic/$(PROGRAM).so: $(OBJECTS)
	@mkdir -p $(BIN_DIR)/dynamic
	$(strip $(CC) -shared -fPIC -o $@ $(OBJECTS))

# Generate a dependency file .d for every source file that tracks includes.
# This allows to see if a source file needs to be recompiled because a header
# file changed.
$(BUILD_DIR)/%.d: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(strip $(CC) $(DEPFLAGS) -o $@ $<)

# Include the dependency files in this makefile. This forces the dependencies
# to be created even if they are not needed, for example with the clean target.
# This could be considered a bug but the only way I now how to fix it is using
# a third-party tool like sed, which I don't want to use.
include $(DEPENDENCIES)

# Build the object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(strip $(CC) $(CFLAGS) -o $@ $<)


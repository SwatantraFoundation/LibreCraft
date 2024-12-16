# Build configuration.
# Copyright (c) 2024, the Swatantra Foundation.
# Provided under the BSD 3-Clause license.

ENABLE_DEBUG = 1
CC = clang
LD = ld.ldd

OFILES = $(addprefix src/,glad.o log.o window.o context.o mat4.o camera.o shader.o texture.o renderer.o main.o)
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lglfw -lm

ifeq ($(OS),Windows_NT)
HOST_OS = Windows
else
HOST_OS = $(shell uname)
endif

ifeq ($(HOST_OS),Windows)
EXENAME = LibreCraft.exe
else
EXENAME = LibreCraft
endif

ifeq ($(ENABLE_DEBUG),1)
CFLAGS += -DENABLE_DEBUG
endif

.PHONY: all
all: $(EXENAME)

$(EXENAME): $(OFILES)
	@echo Linking $@...
	@$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	@echo Compiling $<...
	@$(CC) -c $< $(CFLAGS) -o $@

.PHONY: clean
clean:
	@echo Cleaning...
	@rm -f $(OFILES)

.PHONY: test
test:
	@echo Testing $(EXENAME)...
ifeq ($(HOST_OS),Windows)
	@$(EXENAME) $(EXEFLAGS)
else
	@./$(EXENAME) $(EXEFLAGS)
endif

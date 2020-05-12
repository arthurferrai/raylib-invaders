# HERE LIES CONFIG FOR ALL MAKE ENVIRONMENTS
# SPECIFIC CONFIGURATION SHOULD BE ON SYSTEM SPECIFIC MAKEFILE

PROJECT_NAME = raylib_invaders
PROJECT_VERSION = 1.0.0
# icon must be a 1024x1024 png (without extension)
PROJECT_ICON = icon

# default compilers
# C compiler
CC = gcc
# C++ compiler
CXX = g++
# extra c/c++ preprocessor and compiler flags
EXTRA_CFLAGS =
# extra linker flags (used to link to final binary)
EXTRA_LDFLAGS = -L./lib/raylib -lraylib

# paths
# include dirs
INCLUDE = -I./lib/raylib -I./src
# source dirs (defaults to current and all subdirs)
SRCDIRS =

# compiler and preprocessor flags for C
CFLAGS =
# compiler and preprocessor flags for C++
CXXFLAGS = -std=c++14

# Add optimizations only if DEBUG is not defined
ifndef DEBUG
  CFLAGS += -O3
	CXXFLAGS += -O3
endif

# The C Preprocessor options (notice here "CPP" does not mean "C++"; man cpp for more info.). Actually $(INCLUDE) is included.
CPPFLAGS = -Wall -Wextra    # helpful for writing better code (behavior-related)

# build path
BUILD_PATH = build
OBJ_DIR = obj

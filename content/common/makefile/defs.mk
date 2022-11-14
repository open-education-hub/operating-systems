CC = gcc

# Get the relative path to the directory of the current makefile.
MAKEFILE_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
UTILS_DIR := $(MAKEFILE_DIR)../utils
LOGGER_DIR := $(UTILS_DIR)/log

CPPFLAGS += -I$(UTILS_DIR) -I$(LOGGER_DIR)
CFLAGS += -g -Wall -Wextra
LOGGER_OBJ = log.o
LOGGER = $(LOGGER_DIR)/$(LOGGER_OBJ)

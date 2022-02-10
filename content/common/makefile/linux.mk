# Get the relative path to the directory of the current makefile.
MAKEFILE_DIR = $(dir $(lastword $(MAKEFILE_LIST)))
include $(MAKEFILE_DIR)defs.mk

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

$(LOGGER_OBJ): $(LOGGER_DIR)/log.c
	@make -C $(LOGGER_DIR) $(LOGGER_OBJ)

$(OBJS): %.o: %.c

clean::
	-rm -f $(OBJS) $(LOGGER)

.PHONY: clean

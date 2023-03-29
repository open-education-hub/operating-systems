all: $(BINARY)

# Get the relative path to the directory of the current makefile.
MAKEFILE_DIR = $(dir $(lastword $(MAKEFILE_LIST)))
include $(MAKEFILE_DIR)linux.mk

$(BINARY): $(OBJS) $(LOGGER)
	$(CC) $^ $(LDFLAGS) -o $@ $(LDLIBS)

clean::
	-rm -f $(BINARY)

.PHONY: all clean

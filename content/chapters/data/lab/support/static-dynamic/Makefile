.PHONY: all clean

all: hello-dynamic hello-static

include ../../../../../common/makefile/linux.mk

hello-dynamic: hello.o $(LOGGER)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

hello-static: hello.o $(LOGGER)
	$(CC) -static $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean::
	-rm -f hello-dynamic hello-static

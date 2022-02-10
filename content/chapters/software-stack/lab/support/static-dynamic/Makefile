CFLAGS = -Wall
LDFLAGS_STATIC = -static

.PHONY: all clean

all: hello hello_static

hello: hello.o

hello_static: hello.o
	$(CC) $(LDFLAGS_STATIC) -o $@ $^

hello.o: hello.c

clean:
	-rm -f hello_static hello
	-rm -f hello.o
	-rm -f *~

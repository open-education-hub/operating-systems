CFLAGS = -Wall
LDFLAGS = -z lazy

.PHONY: all clean

all: call call2

call: call.o

call.o: call.c

call2: call2.o

call2.o: call2.c

clean:
	-rm -f call call.o a.txt
	-rm -f call2 call2.o
	-rm -f *~

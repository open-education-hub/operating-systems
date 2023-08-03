CFLAGS = -Wall -g -m32 -fno-PIC -fno-stack-protector -Wno-unused-function -mpreferred-stack-boundary=2
LDFLAGS = -m32 

.PHONY: all clean

all: bo nts io

io: io.o

io.o: io.c

nts: nts.o

nts.o: nts

bo: bo.o

bo.o: bo.c

clean:
	-rm -f bo nts io *.o

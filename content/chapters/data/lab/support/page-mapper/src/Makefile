CFLAGS ?= -Wall -Wextra
CPPFLAGS ?= -I../utils

.PHONY: all clean

all: main

main: main.o page_mapper.o ../utils/log/log.o

main.o: main.c page_mapper.h

page_mapper.o: page_mapper.c page_mapper.h ../utils/utils.h

../utils/log/log.o: ../utils/log/log.c ../utils/log/log.h

clean:
	-rm -f main
	-rm -f main.o
	-rm -f page_mapper.o
	-rm -f *~

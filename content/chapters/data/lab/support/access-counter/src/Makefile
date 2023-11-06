CFLAGS ?= -Wall -Wextra
CPPFLAGS ?= -I../utils

.PHONY: all clean

all: access_counter.o ../utils/log/log.o

access_counter.o: access_counter.c ../utils/utils.h ../utils/log/log.h

../utils/log/log.o: ../utils/log/log.c ../utils/log/log.h

clean:
	-rm -f access_counter.o ../utils/log/log.o
	-rm -f *~

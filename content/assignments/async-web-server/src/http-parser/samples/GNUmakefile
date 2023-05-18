CFLAGS = -Wall -g -I..

.PHONY: all clean

all: test_get_request_path

test_get_request_path: test_get_request_path.o ../http_parser.o

../http_parser.o: ../http_parser.c ../http_parser.h
	make -C .. http_parser.o

clean:
	-rm -f *~
	-rm -f *.o
	-rm -f test_get_request_path

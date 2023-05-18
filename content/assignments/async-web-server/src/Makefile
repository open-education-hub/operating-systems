CC = gcc
CPPFLAGS = -DDEBUG -DLOG_LEVEL=LOG_DEBUG
CFLAGS = -Wall -g
LDLIBS = -laio

.PHONY: all build clean pack

build: all

all: aws

aws: aws.o sock_util.o http_parser.o

aws.o: aws.c utils/sock_util.h utils/debug.h utils/util.h http-parser/http_parser.h aws.h

http_parser.o: http-parser/http_parser.c http-parser/http_parser.h
	$(CC) $(CPPFLAGS) -I. $(CFLAGS) -c -o $@ $<

sock_util.o: utils/sock_util.c utils/sock_util.h
	$(CC) $(CPPFLAGS) -I. $(CFLAGS) -c -o $@ $<

pack: clean
	-rm -f ../src.zip
	zip -r ../src.zip aws.c aws.h http-parser/http_parser.c http-parser/http_parser.h \
		utils/sock_util.c utils/sock_util.h utils/debug.h utils/util.h utils/w_epoll.h \
		Makefile

clean:
	-rm -f ../src.zip
	-rm -f *.o
	-rm -f aws

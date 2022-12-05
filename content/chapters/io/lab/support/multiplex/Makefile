BINARY = epoll_echo_server

include ../../../../../common/makefile/single.mk

epoll_echo_server: epoll_echo_server.o ../../../../../common/utils/sock/sock_util.o

../../../../../common/utils/sock/sock_util.o: ../../../../../common/utils/sock/sock_util.c ../../../../../common/utils/sock/sock_util.h

clean::
	-rm -f ../../../../../common/utils/sock/sock_util.o

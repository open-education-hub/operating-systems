BINARIES = server mp_server mt_server

include ../../../../../../common/makefile/multiple.mk

server: server.o ../../../../../../common/utils/sock/sock_util.o

mp_server: mp_server.o ../../../../../../common/utils/sock/sock_util.o

mt_server: mt_server.o ../../../../../../common/utils/sock/sock_util.o
	$(CC) -o $@ $^ -lpthread

../../../../../../common/utils/sock/sock_util.o: ../../../../../../common/utils/sock/sock_util.c ../../../../../../common/utils/sock/sock_util.h

clean::
	-rm -f ../../../../../../common/utils/sock/sock_util.o

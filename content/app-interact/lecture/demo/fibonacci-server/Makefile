BINARIES = server mt_server mp_server mt_pool_server mp_pool_server mp_pool_server_works

include ../../../../../common/makefile/multiple.mk

server: server.o connection.o ../../../../../common/utils/sock/sock_util.o

mt_server: mt_server.o connection.o ../../../../../common/utils/sock/sock_util.o
	$(CC) -o $@ $^ -lpthread

mp_server: mp_server.o connection.o ../../../../../common/utils/sock/sock_util.o

mt_pool_server: mt_pool_server.o task.o connection.o ../../../../../common/utils/sock/sock_util.o
	$(CC) -o $@ $^ -lpthread

mp_pool_server: mp_pool_server.o task.o connection.o ../../../../../common/utils/sock/sock_util.o
	$(CC) -o $@ $^ -lpthread

mp_pool_server_works: mp_pool_server_works.o connection.o ../../../../../common/utils/sock/sock_util.o

server.o: connection.h

mt_server.o: connection.h

mp_server.o: connection.h

mt_pool_server.o: task.h connection.h

mp_pool_server.o: task.h connection.h

mp_pool_server_works.o: connection.h

connection.o: connection.h

task.o: task.h

../../../../../common/utils/sock/sock_util.o: ../../../../../common/utils/sock/sock_util.c ../../../../../common/utils/sock/sock_util.h

clean::
	-rm -f ../../../../../common/utils/sock/sock_util.o

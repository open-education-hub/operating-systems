CC = gcc
CFLAGS = -Wall -g

all: password-cracker-multiprocess password-cracker-multithread

password-cracker-multiprocess: password-cracker-multiprocess.c log.o
	$(CC) $(CFLAGS) -o $@ $^ -lcrypto

password-cracker-multithread: password-cracker-multithread.c log.o
	$(CC) $(CFLAGS) -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -o $@ $^ -lcrypto -lpthread

log.o: ../utils/log/log.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f password-cracker-multiprocess 	password-cracker-multithread

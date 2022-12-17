CC = gcc
CFLAGS = -Wall -g

all: password-cracker-multiprocess

password-cracker-multiprocess: password-cracker-multiprocess.c log.o
	$(CC) $(CFLAGS) -o $@ $^ -lcrypto

log.o: ../utils/log/log.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f password-cracker-multiprocess

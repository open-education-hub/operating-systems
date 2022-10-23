CC = gcc
CFLAGS = -Wall -g

all: password-cracker-multiprocess

password-cracker-multiprocess: password-cracker-multiprocess.c
	$(CC) $(CFLAGS) -o $@ $< -lcrypto

clean:
	rm -f password-cracker-multiprocess

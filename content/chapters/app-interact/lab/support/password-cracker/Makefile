CC = gcc
CFLAGS = -Wall -g

all: password-cracker-multiprocess password-cracker-multithread

password-cracker-multiprocess: password-cracker-multiprocess.c
	$(CC) $(CFLAGS) -o $@ $< -lcrypto

password-cracker-multithread: password-cracker-multithread.c
	$(CC) $(CFLAGS) -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -o $@ $< -lcrypto -lpthread

clean:
	rm -f password-cracker-multiprocess 	password-cracker-multithread

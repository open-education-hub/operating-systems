CC = gcc
CFLAGS = -Wall

all: server client

server: server.c log.o
	$(CC) $(CFLAGS) -o $@ $^

client: client.c log.o
	$(CC) $(CFLAGS) -o $@ $^

log.o: ../utils/log/log.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f server client

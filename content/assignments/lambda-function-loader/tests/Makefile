SRCDIR?=$(abspath ../src)
CC=gcc
CFLAGS=-fPIC -Wall -Werror
LDLIBS=$(SRCDIR)/libipc.so
CLIENT_LIBS=libbasic.so libadvanced.so libspecial.so

.PHONY: build clean check
build: client $(CLIENT_LIBS)

check:
	./checker.sh $(TEST)

client: client.o $(LDLIBS)

client.o: client.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(LDLIBS):
	@$(MAKE) -C $(SRCDIR) -f Makefile $(foreach LIB,$(LDLIBS),$(notdir $(LIB)))

lib%.so: %.o
	$(CC) $(LDFLAGS) -shared -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf *.o client *.so output ref/big ref/test[569]
	@$(MAKE) -C $(SRCDIR) -f Makefile clean

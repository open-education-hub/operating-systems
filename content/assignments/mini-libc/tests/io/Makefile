LIBC_PATH ?= ../../libc
CPPFLAGS = -nostdinc -I. -I$(LIBC_PATH)/include
CFLAGS = -Wall -Wextra -fno-PIC -fno-stack-protector -fno-builtin
# Remove the line below to disable debugging support.
CFLAGS += -g -O0
LDFLAGS = -nostdlib -no-pie -L$(LIBC_PATH)
LDLIBS = -lc

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
EXECS = $(patsubst %.c,%,$(SRCS))


.PHONY: all clean libc

all: $(EXECS)

$(EXECS): %: %.o | libc
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJS): %.o:%.c

libc:
	make -C $(LIBC_PATH)

clean:
	-rm -f *~
	-rm -f $(OBJS)
	-rm -f $(EXECS)

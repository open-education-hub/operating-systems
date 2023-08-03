SRC_PATH ?= ../src
CPPFLAGS = -nostdinc -I. -I$(SRC_PATH)/include
CFLAGS = -Wall -Wextra -fno-PIC -fno-stack-protector -fno-builtin
# Remove the line below to disable debugging support.
CFLAGS += -g -O0
LDFLAGS = -nostdlib -no-pie -L$(SRC_PATH)
LDLIBS = -lc

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
EXECS = $(patsubst %.c,%,$(SRCS))


.PHONY: all clean src

all: $(EXECS)

$(EXECS): %: %.o | src
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJS): %.o:%.c

src:
	make -C $(SRC_PATH)

clean:
	-rm -f *~
	-rm -f $(OBJS)
	-rm -f $(EXECS)

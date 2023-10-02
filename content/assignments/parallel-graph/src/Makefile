BUILD_DIR := build
CC := gcc
CFLAGS := -c -Wall -g
LD := ld
LDFLAGS :=
LDLIBS := -lpthread

SERIAL_SRCS := serial.c os_graph.c
PARALLEL_SRCS:= parallel.c os_graph.c os_list.c os_threadpool.c
SERIAL_OBJS := $(patsubst $(SRC)/%.c,$(BUILD_DIR)/%.o,$(SERIAL_SRCS))
PARALLEL_OBJS := $(patsubst $(SRC)/%.c,$(BUILD_DIR)/%.o,$(PARALLEL_SRCS))

.PHONY: all pack clean always

all: serial parallel

always:
	mkdir -p build

serial: always $(SERIAL_OBJS)
	$(CC) $(LDFLAGS) -o serial $(SERIAL_OBJS)

parallel: always $(PARALLEL_OBJS)
	$(CC) $(LDFLAGS) -o parallel $(PARALLEL_OBJS) $(LDLIBS)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

pack: clean
	-rm -f ../src.zip
	zip -r ../src.zip *

clean:
	-rm -f ../src.zip
	-rm -rf build
	-rm -f serial parallel

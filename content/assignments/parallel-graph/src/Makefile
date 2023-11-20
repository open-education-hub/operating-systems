BUILD_DIR := build
UTILS_PATH ?= ../utils
CPPFLAGS := -I$(UTILS_PATH)
CFLAGS := -Wall -Wextra
# Remove the line below to disable debugging support.
CFLAGS += -g -O0
PARALLEL_LDLIBS := -lpthread

SERIAL_SRCS := serial.c os_graph.c $(UTILS_PATH)/log/log.c
PARALLEL_SRCS:= parallel.c os_graph.c os_threadpool.c $(UTILS_PATH)/log/log.c
SERIAL_OBJS := $(patsubst %.c,%.o,$(SERIAL_SRCS))
PARALLEL_OBJS := $(patsubst %.c,%.o,$(PARALLEL_SRCS))

.PHONY: all pack clean always

all: serial parallel

serial: $(SERIAL_OBJS)
	$(CC) -o $@ $^

parallel: $(PARALLEL_OBJS)
	$(CC) -o $@ $^ $(PARALLEL_LDLIBS)

$(UTILS_PATH)/log/log.o: $(UTILS_PATH)/log/log.c $(UTILS_PATH)/log/log.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

pack: clean
	-rm -f ../src.zip
	zip -r ../src.zip *

clean:
	-rm -f $(SERIAL_OBJS) $(PARALLEL_OBJS)
	-rm -f serial parallel
	-rm -f *~

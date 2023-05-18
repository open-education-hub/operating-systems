CC = gcc
CFLAGS = -Wall -fPIC
LDFLAGS = -nostdlib -shared
LDLIBS= -lc -ldl
LD = ld

LIBS = sockop_preload.so

all: $(LIBS)

sockop_preload.so: sockop_preload.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	-rm -f $(LIBS)
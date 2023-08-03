TEST = test_ult
LIBULT = libult.so

all: $(TEST) $(LIBULT)

include ../../../../../common/makefile/linux.mk

LIB_OBJECTS = queue.o tcb.o threads.o
TEST_OBJECTS = test_ult.o $(LOGGER)
LDFLAGS = -L.
LDLIBS = -lult

$(TEST): $(TEST_OBJECTS) $(LIBULT)
	$(CC) -o $@ $(TEST_OBJECTS) $(LDFLAGS) $(LDLIBS)

$(LIBULT): $(LIB_OBJECTS)
	$(CC) -shared -o $@ $^

clean::
	rm -f $(TEST) $(LIBULT)

.PHONY: all clean

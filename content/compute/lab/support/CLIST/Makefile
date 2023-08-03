TARGET = test
TARGET_PARALLEL = test_parallel

all: $(TARGET) $(TARGET_PARALLEL)

include ../../../../../common/makefile/linux.mk

LIB_OBJECTS = clist.o
LIBRARY = libclist.a
TEST_OBJECTS = test.o $(LIBRARY)
TEST_OBJECTS_PARALLEL = test_parallel.o $(LIBRARY)

LDLIBS = -lpthread

$(LIBRARY): $(LIB_OBJECTS)
	ar rcs $(LIBRARY) $(LIB_OBJECTS) 

$(TARGET): $(TEST_OBJECTS)
	$(CC) $^ -o $@ $(LDLIBS)

$(TARGET_PARALLEL): $(TEST_OBJECTS_PARALLEL)
	$(CC) $^ -o $@ $(LDLIBS)
		
clean::
	-rm -f $(LIBRARY) $(TARGET) $(TARGET_PARALLEL)

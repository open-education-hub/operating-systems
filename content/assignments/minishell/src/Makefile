UTIL_PATH ?= ../util
CPPFLAGS += -I.
CC = gcc
CFLAGS = -g -Wall
OBJ_PARSER = $(UTIL_PATH)/parser/parser.tab.o $(UTIL_PATH)/parser/parser.yy.o
OBJ = main.o cmd.o utils.o
TARGET = mini-shell
.PHONY = build clean build_parser

all: $(TARGET)

$(TARGET): build_parser $(OBJ) $(OBJ_PARSER)
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_PARSER) -o $(TARGET)

build_parser:
	$(MAKE) -C $(UTIL_PATH)/parser/

pack: clean
	-rm -f ../src.zip
	zip -r ../src.zip *

clean:
	-rm -f ../src.zip
	-rm -rf $(OBJ) $(OBJ_PARSER) $(TARGET) *~

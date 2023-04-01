CC=gcc
CFLAGS=-g -Wall
OBJ_PARSER=../util/parser/parser.tab.o ../util/parser/parser.yy.o
OBJ=main.o cmd.o utils.o
TARGET=mini-shell
.PHONY=build clean build_parser

build: $(TARGET)

$(TARGET): build_parser $(OBJ) $(OBJ_PARSER)
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_PARSER) -o $(TARGET)

build_parser:
	$(MAKE) -C ../util/parser/

clean:
	rm -rf $(OBJ) $(OBJ_PARSER) $(TARGET) *~

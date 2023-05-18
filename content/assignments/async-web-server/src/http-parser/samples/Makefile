#CPPFLAGS = /DDEBUG /DLOG_LEVEL=LOG_DEBUG /I. /I.. /I../..
CPPFLAGS = /I. /I.. /I../..
CFLAGS = /nologo /TP /W3 /EHsc $(CPPFLAGS)
LINK = link

build: all

all: test_get_request_path.exe

test_get_request_path.exe: test_get_request_path.obj ../http_parser.obj
	$(LINK) /nologo /out:$@ $**

../http_parser.obj: ../http_parser.c ../http_parser.h
	$(CC) $(CFLAGS) /c /Fo$@ ../http_parser.c

test_get_request_path.obj: test_get_request_path.c ../http_parser.h
	$(CC) $(CFLAGS) /c /Fo$@ test_get_request_path.c

clean:
	del /Q /S *.obj
	del /Q /S *~
	del /Q /S test_get_request_path.exe

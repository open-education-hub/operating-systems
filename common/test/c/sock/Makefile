BINARY = http_reply_once

include ../../../../common/makefile/single.mk

http_reply_once: http_reply_once.o ../../../../common/utils/sock/sock_util.o

../../../../common/utils/sock/sock_util.o: ../../../../common/utils/sock/sock_util.c ../../../../common/utils/sock/sock_util.h

clean::
	-rm -f ../../../../common/utils/sock/sock_util.o

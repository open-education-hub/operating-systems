BINARIES = send_receive_pipe reader writer \
	   send_fifo receive_fifo \
	   send_unix_socket receive_unix_socket \
	   send_net_dgram_socket receive_net_dgram_socket \
	   send_net_stream_socket receive_net_stream_socket

include ../../../../../common/makefile/multiple.mk

../../../../../common/utils/sock/sock_util.o: ../../../../../common/utils/sock/sock_util.c

send_net_stream_socket: ../../../../../common/utils/sock/sock_util.o

receive_net_stream_socket: ../../../../../common/utils/sock/sock_util.o

clean::
	-rm -f socket_channel
	-rm -f fifo_channel

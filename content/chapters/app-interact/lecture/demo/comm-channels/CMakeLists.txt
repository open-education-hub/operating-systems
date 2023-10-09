link_libraries(utils)

add_executable(send_receive_pipe send_receive_pipe.c)

add_executable(reader reader.c)
add_executable(writer writer.c)

add_executable(send_fifo send_fifo.c)
add_executable(receive_fifo receive_fifo.c)

add_executable(send_unix_socket send_unix_socket.c)
add_executable(receive_unix_socket receive_unix_socket.c)

add_executable(send_net_dgram_socket send_net_dgram_socket.c)
add_executable(receive_net_dgram_socket receive_net_dgram_socket.c)

add_executable(send_net_stream_socket send_net_stream_socket.c)

target_link_libraries(send_net_stream_socket PRIVATE sock_util)

add_executable(receive_net_stream_socket receive_net_stream_socket.c)

target_link_libraries(receive_net_stream_socket PRIVATE sock_util)

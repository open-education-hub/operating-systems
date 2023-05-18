Use make to compile the echo server and the HTTP request reply once server.

$ make


== HTTP reply once server ==

Start reply once server then use an HTTP client (such as wget) to request a
resource and then receive a reply. You may also use a GUI browser. The server
URL should be http://localhost:28282.

# on one console
$ ./http_reply_once

# on the second console
$ wget http://localhost:28282


== epoll-based echo server ==

Start the server and use telnet to connect to server and send messages. The
server will reply with the same message. The server listens for connections
on port 42424.

# on one console
$ ./epoll_echo_server

# on the second, third, ... console
$ telnet localhost 42424

The server uses epoll for multiplexing connections and receiving
notifications (input - EPOLLIN and output - EPOLLOUT). A specialized
structure (struct connection) maintains information regarding each
connection.

Wrappers over epoll are defined in ../w_epoll.h.

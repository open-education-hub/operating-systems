# epoll echo-reply server

Use `make` to compile the `epoll()`-based echo-reply server:

```console
student@os:/.../multiplex/c$ make
```

Start the server and use `telnet` to connect to it and send messages.
The server will reply with the same message.
The server listens for connections on port `42424`.

```console
student@os:/.../multiplex/c$ # on one console
student@os:/.../multiplex/c$ ./epoll_echo_server

student@os:/.../multiplex/c$ # on the second, third, ... console
student@os:/.../multiplex/c$ telnet localhost 42424
```

The server uses `epoll()` for multiplexing connections and receiving notifications (input - `EPOLLIN` and output - `EPOLLOUT`).
A specialized structure (`struct connection`) maintains information regarding each connection.

Wrappers over `epoll()` are defined in `../../../utils/sock/w_epoll.h`.

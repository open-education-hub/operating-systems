# I/O Multiplexing

I/O multiplexing is the ability to serve multiple I/O channels (or anything that can be referenced via a file descriptor / handle) simultaneously.
If a given application, such a server, has multiple sockets on which it serves connection, it may be the case that operating on one socket blocks the server.
One solution is using asynchronous operations, with different backends.
The other solution is using I/O multiplexing.

With I/O multiplexing, the API provides a structure / an array to list all used channels.
And then it provides an API to operate on that channel.
And a (blocking) function to retrieve the channel that is ready for interaction (or channels).
So instead of waiting for a given channel (while others may be ready), you now simultaneously wait on all channels, and the ready channel is returned by the function.

The classical functions for I/O multiplexing are [`select`](https://man7.org/linux/man-pages/man2/select.2.html) and [`poll`](https://man7.org/linux/man-pages/man2/poll.2.html).
Due to several limitations, modern operating systems provide advanced (non-portable) variants to these:

* Windows provides [I/O completion ports (IOCP)](https://learn.microsoft.com/en-us/windows/win32/fileio/i-o-completion-ports).
* BSD provides [`kqueue`](https://www.freebsd.org/cgi/man.cgi?kqueue).
* Linux provides [`epoll()`](https://man7.org/linux/man-pages/man7/epoll.7.html).

**Note** that I/O multiplexing is orthogonal to asynchronous operations.
You could tie them together if the completion of the asynchronous operation sends a notification that can be handled via a file descriptor / handle.
This is the case with Windows asynchronous I/O (called [overlapped I/O](https://learn.microsoft.com/en-us/windows/win32/fileio/synchronous-and-asynchronous-i-o)).

## Practice

Enter the `multiplex/` directory.
See the implementation of an `epoll()`-based server in `epoll_echo_server.c`.

1. Build the server:

   ```console
   student@os:~/.../lab/support/multiplex$ make
   gcc -g -Wall -Wextra -I../../../../../common/makefile/..  -c -o epoll_echo_server.o epoll_echo_server.c
   gcc -g -Wall -Wextra -I../../../../../common/makefile/..  -c -o ../../../../../common/makefile/../utils/log/log.o ../../../../../common/makefile/../utils/log/log.c
   gcc -g -Wall -Wextra -I../../../../../common/makefile/..  -c -o ../../../../../common/utils/sock/sock_util.o ../../../../../common/utils/sock/sock_util.c
   gcc epoll_echo_server.o ../../../../../common/makefile/../utils/log/log.o ../../../../../common/utils/sock/sock_util.o  -o epoll_echo_server
   ```

   And run it:

   ```console
   student@os:~/.../lab/support/multiplex$ ./epoll_echo_server
   08:41:07 INFO  epoll_echo_server.c:252: Server waiting for connections on port 42424
   ```

   It listens for connection on port `42424`.

   Connect using `netcat` on another console and send messages:

   ```console
   $ nc localhost 42424
   aaa
   aaa
   bbb
   bbb
   ```

   Keep the connection open and, on the third console, initiate another `netcat` connection.
   The server is now multiplexing both connections.

1. Create a script and / or a program to exercise the server.
   Create many connections to the server and continuously send messages to the server.
   See it multiplex the I/O channels (one for each connection - actually two: one for receiving and one for sending).

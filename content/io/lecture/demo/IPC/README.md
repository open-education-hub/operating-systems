# IPC

These are some examples on the interprocess communication.

## Build

To build the C examples on Linux, run `make`.

## Running

### Pipe

We use the `pipe()` to create a pipe and `fork()` to create another process.
The parent will write at one end of the pipe and the child will read from the other.

Expected output:

```console
student@os:~/.../demo/IPC$ ./pipe
I am the one who knocks!
```

### FIFO

We use the `mkfifo()` to create a pipe and then proceed to open it from two processes.
The parent will write at one end of the pipe and the child will read from the other.

The pipe created with `mkfifo()` is stored on disk as a **special file**.

```console
student@OS:~$ ls -l my_fifo
prw-r--r-- 1 student student 0 nov 22 18:38 my_fifo
```

Expected output:

```console
student@os:~/.../demo/IPC$ ./fifo
I am the one who knocks!
```

### UNIX Sockets

#### Stream Sockets

We use **UNIX stream sockets** to send a message to a server and wait for it to response with the exact same string.
This example is best followed using two terminals.

First we start the server, which will block waiting for a connection.

```console
student@os:~/.../demo/IPC$ ./unix_stream_socket_server
```

We then start the client, which will send the string to the server and will wait for the response.

```console
student@os:~/.../demo/IPC$ ./unix_stream_socket_client
Received: R2-D2 is underrated
```

The server output is also updated, displaying the received string.

```console
student@os:~/.../demo/IPC$ ./unix_stream_socket_server
Received: R2-D2 is underrated
```

#### Datagram Sockets

We use **UNIX datagram sockets** to send a message to a server and wait for it to response with the exact same string.

When using **UNIX datagram sockets** we also need to bind the client to a socket path in order to receive a reply.

The output is similar to [UNIX Stream Sockets](#unix-sockets).

### Network Sockets

#### Stream Sockets

We use **stream sockets** to send a message to a server and wait for it to response with the exact same string.

The output is similar to [UNIX Sockets](#unix-sockets).

#### Datagram Sockets

We use **datagram sockets** to send a message to a server and wait for it to response with the exact same string.

The output is similar to [UNIX Sockets](#unix-sockets).

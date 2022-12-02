# Beyond Network Sockets

Up until this point, we first learned how to use the [Berkeley Sockets API](./remote-io.md#api---hail-berkeley-sockets), then we learned what a [client and a server is](./client-server-model.md), based on this API.
So now we know that sockets offer a ubiquitous interface for inter-process communication, which is great.
A program written in Python can easily send data to anther one written in C, D, Java, Haskell, you name it.
However, in the [section dedicated to networking](./networking-101.md) we saw that it takes a whole stack of protocols to send this message form one process to the other.
As you might imagine, this is **much slower even than local I/O using files**.

So far we've only used sockets for local communication and in practice it is a bit counterproductive to use network sockets for local IPC due to their high latency.
Wouldn't it be great if we had a means to use the sockets API for local IPC without having to deal with this increased latency?
Well, there is a way and it's alled **UNIX sockets**.

## UNIX Sockets

UNIX sockets allow us to create them using the `socket()` syscall and `bind()` them **TO A FILE** instead of an IP and port.
You may already see a similarity with [named pipes](./pipes.md#named-pipes---mkfifo).
Just like them, UNIX sockets don't work by writing data to the file (that would be slow), but instead the kernel retains the data they send internally so that `send()` and `recv()` can read it from the kernel's storage.
You can use `read()` and `write()` to read/write data from/to both network and UNIX sockets as well, by the way.
The differences between using `send()`/`recv()` or `write()`/`read()` are rather subtle and are described in [this Stack Overflow thread](https://stackoverflow.com/questions/1790750/what-is-the-difference-between-read-and-recv-and-between-send-and-write).

### Practice: Receive from UNIX Socket

Navigate to `support/receive-challenges/receive_unix_socket.c`.
Don't write any code yet.
Let's compare UNIX sockets with network sockets first:

- To create them, give `socket()` the `PF_UNIX`/`AF_UNIX` instead of `PF_INET`/`AF_INET`.
The latter are used to create network sockets.
You can use `PF_*` or `AF_*` interchangeably.
They mean "protocol families" and "address families", respectively, but they are [essentially the same thing](https://stackoverflow.com/a/6737450).
But apart from this, UNIX sockets can be set to work in both TCP (`SOCK_STREAM`) and UDP (`SOCK_DGRAM`) modes.

- The `bind()` call now takes a path as argument, as specified [in the UNIX socket man page](https://man7.org/linux/man-pages/man7/unix.7.html).

And this is it.
Everything else is the same.

Now fill in the `TODO`s in `receive_unix_socket.c`.
Use the example at the bottom of [the UNIX socket man page](https://man7.org/linux/man-pages/man7/unix.7.html) if you get stuck at `bind()`.
When you're done, run compile and it first and then `send_unix_socket`.
If you did this task correctly, `receive_unix_socket` should display the flag.

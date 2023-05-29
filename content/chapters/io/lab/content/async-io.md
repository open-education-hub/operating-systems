# Asynchronous I/O

When doing I/O, the major issue we are facing is that I/O operations are typically much slower than CPU operations.
Because of that, in a typical synchronous scenario, a lot of time may be spent waiting for an I/O operation to be complete.

Because of that, we have other types of I/O operations.

The simplest type of I/O operating is a synchronous, blocking operation.
In this operation type, we call a given function (such as `read()` or `write()`) and wait until it completes.

Another type of operation is a non-blocking operation.
In this type of operation, if data isn't available (in case of `read()`) or can not be sent (in case of `write()`), the given call will not block, it will simply return with a mark to try again later on.

Another type of operation is an asynchronous operation.
In the case of an asynchronous operation, the given function returns immediately and the program continues its execution.
Once the operation succeeds, a notification may be sent out to the program.
Or the program can periodically check the state of the operation.

Apart from these operating types, there is the option to do I/O multiplexing, i.e. the ability to tackle multiple channels simultaneously.
This is useful in case of servers, that get a large number of requests and have to iterate through them.

In case of asynchronous I/O, the "backend" used to implement the operations may differ:

1. It can be a multiprocess backend, where each action / request is passed to a given process.

1. It can be a multithreaded backend, where each action / request is passed to a given thread.

1. It can be an event-based backend, where an action is scheduled together with a callback that is invoked when an action ends.

## Practice

Enter the `support/async/` folder for some implementations of a simple request-reply server in Python or in C.
The server gets requests and serves them in different ways: synchronous, multiprocess-based, multi-threading-based, asynchronous.

We use two implementations, in Python and in C.

1. For the Python implementation, enter the `python/` subdirectory.
   Take a look at the implementation of different servers:

   * synchronous server: `server.py`
   * multiprocess backend: `mp_server.py`
   * multithreaded backend: `mt_server.py`
   * asynchronous API backend: `async_server.py` (requires Python >= 3.7) and `async_server_3.6.py` (works for Python 3.6)

   Let's do a benchmarking session of each server type.
   For this we will:

   1. Start the server on one console.

   1. Use the `client_bench.sh` script to benchmark the server.
      `client_bench.sh` is a simple script that starts multiple clients to connect to the servers, by running `client.py`.
      It runs `NUM_CLIENT` instances of `client.py` to trigger actions in the remote server.

      **Note** that you may be required to run servers on different ports in case of an `Address already in use error`.
      If that is the case, you will also need to run the `client_bench.sh` script.

   To start the server, run each of these commands (one at a time to test the respective server type):

   ```console
   student@os:/.../support/async/python$ ./server.py 2999

   student@os:/.../support/async/python$ ./mp_server.py 2999

   student@os:/.../support/async/python$ ./mt_server.py 2999

   student@os:/.../support/async/python$ ./async_server_3.6.py 2999
   ```

   For each server, in a different console, we can test to see how well it behaves by running:

   ```console
   student@os:/.../support/async/python$ time ./client_bench.sh
   ```

   You will see a time duration difference between `mp_server.py` and the others, `mp_server.py` runs requests faster.
   This is because the multiprocess model works OK for a CPU-intensive server such as this.

   But not on threading, because threading suffers from the use of [GIL (_Global Interpreter Lock_)](https://realpython.com/python-gil/), that prevents multithreaded programs from running Python code simultaneously.

1. For the C implementation, enter the `c/` subdirectory.
   Take a look at the implementation of different servers:

   * synchronous server: `server.c`
   * multiprocess backend: `mp_server.c`
   * multithreaded backend: `mt_server.c`

   There is no asynchronous C variant, because of the unstable API of [`libaio`](https://pagure.io/libaio) and [`io_uring`](https://unixism.net/loti/what_is_io_uring.html).

   First, use `make` to build the servers.
   Then, go through the same steps as above:

   1. Start the server on one console.

   1. Use the `client_bench.sh` script (in the `../python/` directory) to benchmark the server.

   Same as with Python, to start the server, run each of these commands (one at a time to test the respective server type):

   ```console
   student@os:/.../support/async/c$ ./server 2999

   student@os:/.../support/async/c$ ./mp_server 2999

   student@os:/.../support/async/c$ ./mt_server 2999
   ```

   For each server, in a different console, we can test to see how well it behaves by running:

   ```console
   student@os:/.../support/async/python$ time client_bench.sh
   ```

   We draw 2 conclusions from using the C variant:

   1. C is faster than Python
   1. The thread variant is indeed parallel, as now the GIL is no longer involved.

## Remarks

Asynchronous operations, as with others, provide an API, as is the case with the Python API or the [`libaio`](https://pagure.io/libaio) and [`io_uring`](https://unixism.net/loti/what_is_io_uring.html).
The backend of these operations may be a thread-based one in the library providing the API, or it may rely on support from the operating system.
When aiming for performance, asynchronous I/O operations are part of the game.
And it's very useful having a good understanding of what's happening behind the scenes.

For example, for the Python `async_server_3.6.py` server, a message `asyncio: Using selector: EpollSelector` is provided.
This means that the backend relies on the use of the [`epoll()` function](https://man7.org/linux/man-pages/man7/epoll.7.html) that's part of the [I/O Multiplexing section](./io-multiplexing.md).

Also, for Python, the use of the GIL may be an issue when the operations are CPU intensive.

This last point deserves a discussion.
It's rare that servers or programs using asynchronous operations are CPU intensive.
It's more likely that they are I/O intensive, and the challenge is avoiding blocking points in multiple I/O channels;
not avoiding doing a lot of processing, as is the case with the `fibonacci()` function.
In that particular case, having thread-based asynchronous I/O and the GIL will be a good option, as you rely on the thread scheduler to be able to serve multiple I/O channels simultaneously.
This later approach is called I/O multiplexing, discussed in [the next section](./io-multiplexing.md).

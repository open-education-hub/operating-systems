# Optimizations

These are some examples on I/O optimizations.

## Build

To build the C examples on Linux, run `make`.

## Running

### `stdout` vs `stderr`

We explore the difference between `stdout` and `stderr` when it comes to IO buffering.

The code prints two interleaved sentences: `"Hello from the other side!"` and `"Join the dark side!"`.
Running the code yields a different result than we would expect.

```console
student@os:~/.../demo/optimizations$ ./stdout-vs-stderr
Join the dark side!
Hello from the other side!
```

Let us investigate using `strace`.

```console
student@os:~/.../demo/optimizations$ strace --trace=write ./stdout-vs-stderr
write(2, "Join the ", 9Join the )                = 9
write(2, "dark side!\n", 11dark side!
)            = 11
write(1, "Hello from the other side!", 26Hello from the other side!) = 26
```

We observe that strings meant for `stdout` are collected and printed only once.
This mechanism is called **buffering** and serves to reduce the number of `write()` syscalls.

Uncomment the `setvbuf()` function to stop the `stdout` buffering.

```console
student@os:~/.../demo/optimizations$ strace --trace=write ./stdout-vs-stderr
write(1, "Hello ", 6Hello )                   = 6
write(1, "from ", 5from )                    = 5
write(1, "the ", 4the )                     = 4
write(2, "Join the ", 9Join the )                = 9
write(1, "other ", 6other )                   = 6
write(1, "side!", 5side!)                    = 5
write(2, "dark side!\n", 11dark side!
)            = 11
```

### `fwrite` 10000

We write **10000 bytes** to a file, **1 byte** at a time with `fwrite()` and use `strace` and `time` to benchmark this solution.

```console
student@os:~/.../demo/optimizations$ strace --trace=write ./fwrite-10000
write(3, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"..., 4096) = 4096
write(3, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"..., 4096) = 4096
write(3, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"..., 1808) = 1808
```

```console
student@os:~/.../demo/optimizations$ time ./fwrite-10000
real    0m0.001s
user    0m0.001s
sys     0m0.000s
```

The default buffer size in `libc` is `4096`, stored in macro `BUFSIZ`.
The `write()` syscalls are triggered when buffer is full, thus reducing the number of syscalls from 10000 to 3.

### `write` 10000

We write **10000 bytes** to a file, **1 byte** at a time with `write()` and use `strace` and `time` to benchmark this solution.

```console
student@os:~/.../demo/optimizations$ strace -c --trace=write ./write-10000
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
100.00    0.377586          37     10000           write
```

```console
student@os:~/.../demo/optimizations$ time ./write-10000
real    0m0.011s
user    0m0.001s
sys     0m0.011s
```

This example serves as a comparison item for `fwrite` and `unbuffered write`.

### `write` 1000 unbuf

We write **1000 bytes** to a file, **1 byte** at a time with unbuffered `write()` and use `strace` and `time` to benchmark this solution.

```console
student@os:~/.../demo/optimizations$ strace -c --trace=write ./write-1000-unbuf
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
100.00    0.055044          55      1000           write
```

```console
student@os:~/.../demo/optimizations$ time ./write-1000-unbuf
real    0m2.052s
user    0m0.000s
sys     0m0.087s
```

The performance drawback of dissabling IO buffering is obvious even when operating **1000 bytes** - **10000 bytes** would have been overkill.

### client.py

This is a client that sends an index to a server and expects the fibonacci number with that index.

The client receives the number as argument or randomly generates it.
It proceeds to encode the number and sends it to the server.
After receiving a response it prints it and stops its execution.

```console
student@os:~/.../demo/optimizations$ python client.py localhost 1234 6
root: Connected to localhost:1234
root: Sending 6
function(6): 13
```

### server.py

We use a remote server to compute the nth fibonacci number which is given as parameter by a client.

After configuring the server we start it in a loop and call `handle()` for each new connection.
`handle()` ensures that received argument is correct and starts computation.
The result is encoded and sent back to the client.

```console
student@os:~/.../demo/optimizations$ python server.py 1234
root: Starting server on port 1234
root: Received connection from ('127.0.0.1', 44834)
root: Message: 6
```

### mp_server.py

See [server.py](#serverpy).

### mt_server.py

See [server.py](#serverpy).

### async_server.py

See [server.py](#serverpy).

### client_bench.sh

This is a simple bash script that receives the port of a running server as argument and proceeds to run multiple `client.py` instances.

```console
student@os:~/.../demo/optimizations$ time ./client_bench.sh 1234
root: Connected to localhost:1234
root: Sending 30
root: Connected to localhost:1234
root: Sending 30
[...]
function(30): 1346269
function(30): 1346269

real    0m1.318s
user    0m0.225s
sys     0m0.048s
```

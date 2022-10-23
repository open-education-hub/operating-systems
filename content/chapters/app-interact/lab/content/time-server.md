## Time Server

Check out the code in `support/time-server/server.c` and `support/time-server/client.c`.

This is a simple program consisting of a server and a client.
The server uses a tcp socket to wait for connections.
Once a client has connected, the server will send the current time to it.
The client will then print the received time to the console.

Let's build and run this example

```
student@os:~/.../lab/time-server$ make
gcc -Wall -o server server.c
gcc -Wall -o client client.c
student@os:~/.../lab/time-server$ ./server
```

Then, in another terminal
```
student@os:~/.../lab/time-server$ ./client 127.0.0.1 2000
The time is Thu Sep  1 11:48:03 2022
```

### Python version

In `support/time-server/python` we have the equivalent python implementation for both the server and client.

```
student@os:~/.../lab/time-server/python$ python3 server.py
```

```
student@os:~/.../lab/time-server/python$ python3 client.py 127.0.0.1 2000
The time is Thu Sep  1 11:58:01 2022
```

#### Practice

Try to figure out the protocol used by the server and the client.
You can do this by reading the source code, corroborated with information obtained at runtime.

Run the server again (the version in C), but instead of running the client let's run `netcat` and pipe the output to `hexdump`:

```
nc -d 127.0.0.1 2000 | hexdump -C
```

[Quiz](../quiz/time-server.md)

[Quiz](../quiz/time-server-interop.md)

# Time Server Interoperability

## Question Text

Is the protocol between the python server and the python client the same?
Can we run the python server and connect to it via the C client?

## Question Answers

+ Yes

- No, the protocols are different

## Feedback

By doing the same investigation on the python server we discover that the protocol is the same.
This means that we can run the python server and the C client, or the C server and python client, and everything will work:

```console
student@os:~/.../support/time-server/python$ python3 server.py
```

```console
student@os:~/.../support/time-server$ ./client 127.0.0.1 2000
The time is Thu Sep  1 11:48:03 2022
```

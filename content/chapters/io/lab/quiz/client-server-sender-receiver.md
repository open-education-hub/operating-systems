# `sender.py` and `receiver.py` Client-Server Parallel

## Question Text

Drawing a parallel from the UDP examples in `support/send-receive/`, which of the sender and receiver is similar to the server and which is similar to the client?

## Question Answers

- both are similar to clients

- both are similar to servers

+ `receiver.py` is similar to a server and `sender.py` is similar to a client

- `receiver.py` is similar to a client and `sender.py` is similar to a server

## Feedback

`receiver.py` is the passive component.
It has to be started first and then waits for `sender.py` (the client) to send data.
Furthermore, you can only have **one** `receiver.py` running at the same time (remember the [multiple `bind()` bug](./bind-error-cause.md)) and multiple `sender.py`s.

# Cause of `bind()` Error

## Question Text

While `receiver.py` is still running, run it again from another terminal.
You will get an error.
What is its cause?

## Question Answers

- the IP `127.0.0.1` is already used by `receive.py`

+ the port 5000 is already used (by `receive.py`)

- a port may not be used multiple times by the same process

- the socket was not created correctly

## Feedback

One port may only be bound to **one socket** at a time.
The fact that it's the same program (same source code) using it is irrelevant because they're different processes.

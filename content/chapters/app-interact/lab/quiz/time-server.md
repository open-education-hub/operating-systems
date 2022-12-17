# Time Server Protocol

## Question Text

What format does the message exchanged between the server and the client have?

## Question Answers

- 4 byte length (little endian) followed by 8 byte timestamp (little endian)

- 8 byte length (little endian) followed by 4 byte timestamp (little endian)

+ 4 byte length (big endian) followed by 8 byte timestamp (big endian)

- 8 byte length (big endian) followed by 4 byte timestamp (big endian)

## Feedback

If we consider one output example:

```console
00000000  00 00 00 08 00 00 00 00  63 1b a9 50              |........c..P|
0000000c
```

We can identify the 4 byte length in big endian (`00 00 00 08`), then the 8 byte timestamp (`00 00 00 00  63 1b a9 50`), also in big endian.

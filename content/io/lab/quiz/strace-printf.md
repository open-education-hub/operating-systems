# `printf()` Under Strace

## Question Text

How many calls to `write()` does the code in `support/buffering/printf_buffering.c` do?

## Question Answers

- none

+ 1

- 6

- 5

## Feedback

Just run the binary under `strace`:

```console
student@os:/.../support/buffering$ strace -e write ./printf_buffering
write(1, "Dovahkiin, Dovahkiin Naal ok zin"..., 169Dovahkiin, Dovahkiin Naal ok zin los vahriin Wah dein vokul mahfaeraak ahst vaal! Ahrk fin norok paal graan Fod nust hon zindro zaan Dovahkiin, fah hin kogaan mu draal! ) = 169
+++ exited with 0 +++
```

There's **one** call to `write()`.

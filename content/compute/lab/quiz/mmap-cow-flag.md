# Copy-on-write Flag for `mmap()`

## Question Text

From the description in its [man page](https://man7.org/linux/man-pages/man2/mmap.2.html), what flag should we pass to `mmap()` in order to mark the mapped pages as copy-on-write?

## Question Answers

- `MAP_SHARED`

+ `MAP_PRIVATE`

- `MAP_ANONYMOUS`

- `MAP_POPULATE`

## Feedback

Quoting the [man page](https://man7.org/linux/man-pages/man2/mmap.2.html):

```text
MAP_PRIVATE
              Create a private copy-on-write mapping.
```

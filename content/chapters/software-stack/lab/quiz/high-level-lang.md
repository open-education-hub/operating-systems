# Python Tools

## Question Text

A Python program is not a proper argument for ...

## Question Answers

- `ltrace`

- `strace`

- `rm`

+ `ldd`

## Feedback

Because a Python program is a script to be interpreted, it won't be usable by `ldd`.
`ldd` is passed a binary executable to look for library dependencies.

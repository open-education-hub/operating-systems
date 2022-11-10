# File Descriptor of `stderr`

<!-- markdownlint-disable-file MD004 -->

## Question Text

Which file descriptor is associated by default to `stderr`?

## Question Answers

- it varies from process to process

- it varies from one Linux distribution to another

- `stderr` has no associated file descriptor

+ 2

- 0

- 1

## Feedaback

You would type `ls 2> /dev/null` to ignore `ls`'s errors.
This equates to **redirecting** `stderr` to `/dev/null`.
The number 2 in `2>` hints that `stderr` is by default associated with file descriptor 2.

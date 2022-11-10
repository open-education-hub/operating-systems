# `O_TRUNC` Flag Behaviour

<!-- markdownlint-disable-file MD004 -->

## Question Text

How does the `O_TRUNC` flag change the behaviour of `open()`?

## Question Answers

+ the previous content of the file is deleted

- new data will be appended to the file

- newly written data will be ignored

## Feedback

The man page provides us with unlimited wisdon:

> If the file already exists and is a regular file and the access mode allows writing (i.e., is `O_RDWR` or `O_WRONLY`) it will be truncated to length 0.

Setting the length of the file to 0 is equivalent to deleting the previous content of the file.

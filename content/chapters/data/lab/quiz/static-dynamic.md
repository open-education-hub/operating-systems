# Modify String

## Question Text

What is the granularity of the size of memory sections?

## Question Answers

- 4 bytes

- 4 MB

+ 4 KB

- 1 KB

## Feedback

All sizes of memory areas are multiple of 4 KB (the page size).
Also, all addresses start at multiple of 4 KB.

# Modify String

## Question Text

How many bytes would we need to use to increase the size of the `.data` section in the `hello-static` executable shown in the text to cause a total size of `28 KB`, instead of `24 KB`?

## Question Answers

- 1 KB

- 4 KB

- 3232 bytes

- 3581 bytes

## Feedback

The total size must be `1` byte over the `24 KB` threshold to cause a new page allocation.
So in order to get that past the current size of `20996`, we need `3581` bytes:

```console
$ echo "24 * 1024 + 1 - 20996" | bc
3581
```

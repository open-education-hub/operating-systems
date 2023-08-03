# Page Allocation

## Question Text

```console
student@os:~/.../lab/support/static-dynamic$ size hello-static
text    data     bss     dec     hex filename
893333   20996    7128  921457   e0f71 hello-static
```

How many bytes should we add to the `.data` section to make its size `28 KB`, instead of `24 KB`?

## Question Answers

- 1 KB

- 4 KB

- 3580 bytes

+ 3581 bytes

## Feedback

The total size must be `1` byte over the `24 KB` threshold to cause a new page allocation.
So in order to get that past the current size of `20996`, we need `3581` bytes:

```console
student@os:~$ echo "24 * 1024 + 1 - 20996" | bc
3581
```

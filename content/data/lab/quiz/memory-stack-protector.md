# Stack Protector

## Question Text

For the `support/memory-security/bo_write_practice` executable we are not able overwrite the `s` variable no matter the input.
Why is that?

## Question Answers

- `s` needs to be declared after `buffer`.

+ when using the stack canary, the buffer is always placed right below it.

- due to ASLR, the address of `s` is random.

- the stack canary makes it impossible to overwrite local variables.

## Feedback

When using the canary, to minimize the damage a buffer overflow could cause, the buffers are always placed right below the canary.
By doing so, a buffer overflow will not overwrite anything.
However, it is still possible to overwrite other local buffers, provided that a function declares more than 1 array or if we use the pointer directly.

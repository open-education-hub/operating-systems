# Half Page

## Question Text

```c
char *p = malloc(2 * 1024);
```

What is a potential problem when allocating half a page?

## Question Answers

- It will fragment the virtual memory because users should always request at least one page

- Asking for less than a page might place the memory on two different pages

+ Writing in the other half is allowed

- Allocations smaller than one page should use the stack

## Feedback

The OS allocates memory in chunks of 4 KB (the page size).
Even if we do not need the second half of a page, we have permissions to update it.
This might be a problem because buffer overflows can pass unnoticed.

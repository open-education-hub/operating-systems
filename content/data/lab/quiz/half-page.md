# Half Page

## Question Text

```c
char *p = malloc(2 * 1024);
```

What is a potential problem when allocating half a page?

## Question Answers

- It will fragment the virtual memory because users should always request at least one page

- Asking for less than a page might place the memory on two different pages

+ Writing to the other half may be allowed

- Allocations smaller than one page should use the stack

## Feedback

The OS allocates memory in chunks of 4 KB (the page size).
If the memory we allocate happens to be placed at the beginning of a page, we have permission to update the second half of this page despite not requesting it.
This might be a problem because buffer overflows can pass unnoticed.

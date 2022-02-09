## Question Text

What happens if the following code is executed:

```c
void main()
{
    /* some code, may contain allocations */

    int* arr = malloc(2000*sizeof(int));
    arr[2005] = 10;
}
```

## Question Answers

- Address is valid so no page fault is issued and the code is executed succesfully
- Address is invalid, therefore "Segmentation Fault" is issued
- Address is valid, but no physical mapping exists so a page fault is issued, a physical page is mapped and execution continues
+ all of the above

## Feedback

All of the situations are possible since it depends where inside of a page the start address is.

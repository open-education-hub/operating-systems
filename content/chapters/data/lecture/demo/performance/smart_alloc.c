#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef struct IntArray
{
    size_t capacity;
    size_t len;
    int* ptr;
}IntArray;

IntArray *allocArray(size_t len)
{
    IntArray *arr = malloc(sizeof(IntArray));
    arr->ptr = malloc(3*len*sizeof(int));
    arr->capacity = 3*len;
    arr->len = len;
    return arr;
}

void printArray(IntArray *arr)
{
    for(int i = 0; i < arr->len; i++)
        printf("%d\n", arr->ptr[i]);
}

void appendElem(IntArray* arr, int elem)
{
    if (arr->len >= arr->capacity)
    {
        arr->ptr = realloc(arr->ptr, sizeof(int)*(arr->len*2));
        arr->capacity = arr->len * 3;
    }

    arr->ptr[arr->len] = elem;
    arr->len++;
}

void freeArray(IntArray* arr)
{
    free(arr->ptr);
    free(arr);
}

void main()
{
    IntArray *arr = allocArray(N);
    for (int i = 0; i < arr->len; i++)
        arr->ptr[i] = i;

    printf("======= Initial array ========\n");
    printArray(arr);
    printf("==============================\n");

    for(int i = arr->len; i < N + N; i++)
    {
        appendElem(arr, i);
    }

    printf("======= Final array ==========\n");
    printArray(arr);
    printf("==============================\n");

    free(arr);
}

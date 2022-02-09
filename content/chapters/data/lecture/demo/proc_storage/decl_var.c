#include <stdio.h>

int a = 42;

void main()
{
    printf("Address of var: %lx   || Value  of var: %d", (long unsigned int)&a, a);
    getchar();
    printf("Value of var: %d", a);
}

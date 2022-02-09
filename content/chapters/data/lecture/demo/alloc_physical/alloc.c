#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000000

void main()
{
    volatile int *a = malloc(N * sizeof(int));
    size_t i = 0;
    int sum = 0;
    clock_t start, end;
    double cpu_time_used;


    start = clock();
    for (i = 0; i < N; i++)
        sum += a[i];
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("First loop took: %f\n", cpu_time_used);

    sum = 0;
    start = clock();
    for (i = 0; i < N; i++)
        sum += a[i];
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Second loop took: %f\n", cpu_time_used);
}

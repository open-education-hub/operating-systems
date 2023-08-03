/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>

void main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./write_var addr\n");
        exit(1);
    }
    unsigned long int addr = strtoul(argv[1], NULL, 16);
    int* p = addr;
    printf("Writing at address: %p\n", p);
    *p = 5;
}

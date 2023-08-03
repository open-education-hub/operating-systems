/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "utils/utils.h"

#define COUNT 10000
#define FILENAME "data.txt"

int main()
{
    static const char buf[COUNT] = {'a'};
    FILE *fp;

    fp = fopen(FILENAME, "w");
    DIE(fp == NULL, "fopen");

    for (int i = 0; i < COUNT; i++)
    {
        fwrite(buf, sizeof(char), 1, fp);
    }

    fclose(fp);

    return 0;
}

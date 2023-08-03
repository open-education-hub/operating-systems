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
    int fd;

    fd = open(FILENAME, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    DIE(fd < 0, "open");

    for (int i = 0; i < COUNT; i++)
    {
        DIE((write(fd, buf + i, 1)) < 0, "write");
    }

    close(fd);

    return 0;
}

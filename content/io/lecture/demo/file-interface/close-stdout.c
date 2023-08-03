/* SPDX-License-Identifier: BSD-3-Clause */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils/utils.h"

#define FILENAME        "my_stdout.txt"

static void
wait_for_input(const char *msg)
{
    char buf[32];

    printf(" * %s\n", msg);
    printf(" -- Press ENTER to continue ...\n");
    fflush(stdout);
    fgets(buf, 32, stdin);
}

int main(void)
{
    int rc;
    int fd, dup_fd;

    wait_for_input("Open file");
    fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    DIE(fd < 0, "open");

    wait_for_input("Close stdout");
    rc = close(STDOUT_FILENO);
    DIE(rc < 0, "close");

    wait_for_input("Duplicate the file descriptor");
    dup_fd = dup(fd);
    DIE(dup_fd < 0, "dup");

    printf("This will go to stdout\n");

    wait_for_input("Close the file descriptors");
    close(fd);
    // second_fd will be closed automatically at the end of the program

    return 0;
}

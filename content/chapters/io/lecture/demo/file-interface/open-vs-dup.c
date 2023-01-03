/* SPDX-License-Identifier: BSD-3-Clause */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils/utils.h"

#define FILENAME        "gandalf.txt"
#define COUNT_BYTES     23

static void create_input_file() {
    static const char *content = "A wizard is never late, nor is he early.";

    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    DIE(fd < 0, "open");

    int rc = write(fd, content, strlen(content));
    DIE(rc < 0, "write");

    rc = close(fd);
    DIE(rc < 0, "close");
}

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
    char buf[32];
    int rc, first_fd, second_fd, dup_fd;

    create_input_file();

    wait_for_input("Open file");
    first_fd = open(FILENAME, O_RDONLY);
    DIE(first_fd < 0, "open");

    wait_for_input("Open file again");
    second_fd = open(FILENAME, O_RDONLY);
    DIE(second_fd < 0, "open");

    wait_for_input("Duplicate the first file descriptor");
    dup_fd = dup(first_fd);
    DIE(dup_fd < 0, "dup");

    wait_for_input("Read 23 bytes from first file descriptor");
    memset(buf, 0, 32);
    rc = read(first_fd, buf, COUNT_BYTES);
    DIE(rc < 0, "read");
    printf("%s\n\n", buf);

    wait_for_input("Read 23 bytes from the second file descriptor");
    memset(buf, 0, 32);
    rc = read(second_fd, buf, COUNT_BYTES);
    DIE(rc < 0, "read");
    printf("%s\n\n", buf);

    wait_for_input("Read 23 bytes from the duplicated file descriptor");
    memset(buf, 0, 32);
    rc = read(dup_fd, buf, COUNT_BYTES);
    DIE(rc < 0, "read");
    printf("%s\n\n", buf);

    wait_for_input("Close file descriptors");
    close(first_fd);
    close(second_fd);
    close(dup_fd);

    return 0;
}

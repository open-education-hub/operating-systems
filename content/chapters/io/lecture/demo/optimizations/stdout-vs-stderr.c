/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <unistd.h>

int main()
{
    // setvbuf(stdout, NULL, _IONBF, 0);

    fprintf(stdout, "Hello ");
    fprintf(stdout, "from ");
    fprintf(stdout, "the ");

    fprintf(stderr, "Join the ");

    fprintf(stdout, "other ");
    fprintf(stdout, "side!");

    fprintf(stderr, "dark side!\n");

    return 0;
}

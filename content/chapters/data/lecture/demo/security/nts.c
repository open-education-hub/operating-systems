#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static void see_beyond(const char *s)
{
    int value = 0xaabbccdd;
    char buffer[32];

    if (strlen(s) < 32)
        strcpy(buffer, s);
    else
        memcpy(buffer, s, 32);

    printf("buffer is #%s#\n", buffer);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s string\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    see_beyond(argv[1]);

    return 0;
}

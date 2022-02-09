#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        printf("proc-2  pid  addr  length\n");
        exit(1);
    }

    int           pid  = strtol (argv[1], NULL, 10);
    unsigned long addr = strtoul(argv[2], NULL, 16);
    int           len  = strtol (argv[3], NULL, 10);

    char* proc_mem = malloc(50);
    sprintf(proc_mem, "/proc/%d/mem", pid);

    printf("opening %s, address is %ld\n", proc_mem, addr);
    int fd_proc_mem = open(proc_mem, O_RDWR);
    if (fd_proc_mem == -1)
    {
        printf("Could not open %s\n", proc_mem);
        exit(1);
    }

    char* buf = malloc(len);

    lseek(fd_proc_mem, addr, SEEK_SET);
    read (fd_proc_mem, buf , len     );

    printf("String at %ld in process %d is:\n", addr, pid);
    printf("  %s\n", buf);

    printf("\nNow, this string is modified\n");
    strncpy(buf, "Hello from proc-2", len);

    lseek(fd_proc_mem, addr, SEEK_SET);
    if (write (fd_proc_mem, buf , len     ) == -1)
    {
        printf("Error while writing\n");
        exit(1);
    }

    free(buf);
    free(proc_mem);
}

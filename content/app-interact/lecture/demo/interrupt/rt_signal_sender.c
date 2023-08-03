/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <signal.h>
#include <unistd.h>

#include "utils/utils.h"

int main(int argc, char **argv)
{
	pid_t pid;
	long res;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s PID\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	res = strtol(argv[1], NULL, 10);
	DIE(res == LONG_MIN || res == LONG_MAX, "strtol");

	pid = res;
	kill(pid, SIGRTMIN);
	kill(pid, SIGRTMIN+1);
	kill(pid, SIGRTMIN+2);
	kill(pid, SIGRTMIN+3);
	kill(pid, SIGRTMIN+4);
	kill(pid, SIGRTMIN+5);
	kill(pid, SIGRTMIN+6);
	kill(pid, SIGRTMIN+3);
	kill(pid, SIGRTMIN+7);

	sleep(3);
	kill(pid, SIGTERM);
	kill(pid, SIGKILL);

	return 0;
}

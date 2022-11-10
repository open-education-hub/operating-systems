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
	kill(pid, SIGHUP);
	sleep(1);
	kill(pid, SIGILL);
	sleep(1);
	kill(pid, SIGTRAP);
	sleep(1);
	kill(pid, SIGABRT);
	sleep(1);
	kill(pid, SIGBUS);
	sleep(1);
	kill(pid, SIGFPE);
	sleep(1);
	kill(pid, SIGUSR1);
	sleep(1);
	kill(pid, SIGABRT);
	sleep(1);
	kill(pid, SIGUSR2);

	sleep(3);
	kill(pid, SIGTERM);
	kill(pid, SIGKILL);

	return 0;
}

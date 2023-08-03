/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "utils/log/log.h"

#define LOG_LEVEL	LOG_INFO

static void handler(int signal)
{
	log_debug("signal received: %d", signal);

	switch (signal) {
	case SIGHUP:
		printf("g");
		break;
	case SIGILL:
		printf("e");
		break;
	case SIGTRAP:
		printf("r");
		break;
	case SIGABRT:
		printf("o");
		break;
	case SIGBUS:
		printf("n");
		break;
	case SIGFPE:
		printf("i");
		break;
	case SIGUSR1:
		printf("m");
		break;
	case SIGUSR2:
		printf("\n");
		break;
	}
}

int main(void)
{
	struct sigaction sa;

	setvbuf(stdout, NULL, _IONBF, 0);
	log_set_level(LOG_LEVEL);

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;
	sigfillset(&sa.sa_mask);
	sigaction(SIGHUP, &sa, NULL);
	sigaction(SIGILL, &sa, NULL);
	sigaction(SIGTRAP, &sa, NULL);
	sigaction(SIGABRT, &sa, NULL);
	sigaction(SIGBUS, &sa, NULL);
	sigaction(SIGFPE, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	while (1) {
		sigset_t oldset;
		sigprocmask(0, NULL, &oldset);
		sigsuspend(&oldset);
	}

	return 0;
}

/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "utils/log/log.h"

#define LOG_LEVEL	LOG_INFO

const char messages[] = {'g', 'e', 'r', 'o', 'n', 'i', 'm', '\n'};

static void handler(int signal)
{
	log_debug("signal received: %d", signal);
	printf("%c", messages[signal-SIGRTMIN]);
}

int main(void)
{
	struct sigaction sa;
	int signal;

	setvbuf(stdout, NULL, _IONBF, 0);
	log_set_level(LOG_LEVEL);

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;
	sigfillset(&sa.sa_mask);
	for (signal = SIGRTMIN; signal <= SIGRTMIN+7; signal++)
		sigaction(signal, &sa, NULL);

	while (1) {
		sigset_t oldset;
		sigprocmask(0, NULL, &oldset);
		sigsuspend(&oldset);
	}

	return 0;
}

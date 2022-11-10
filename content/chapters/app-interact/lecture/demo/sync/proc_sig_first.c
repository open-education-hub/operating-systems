/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <signal.h>
#include <unistd.h>

#include "utils/utils.h"

#define SIG	SIGUSR1

static const char * const messages[] = {
	"I",
	"hate",
	"bullshit"
};

static int find_pid_by_name(const char *name)
{
	FILE *p;
	char buf[128];
	long res;

	sprintf(buf, "pgrep %s", name);
	p = popen(buf, "r");
	DIE(p == NULL, "popen");

	fgets(buf, 128, p);

	res = strtol(buf, NULL, 10);
	DIE(res == LONG_MIN || res == LONG_MAX, "strtol");

	return (int) res;
}

static void block_signal(int signal)
{
	sigset_t block_set;

	sigemptyset(&block_set);
	sigaddset(&block_set, signal);
	sigprocmask(SIG_BLOCK, &block_set, NULL);
}

static void send_signal_to_process_by_name(int signal, const char *name)
{
	pid_t pid;
	int rc;

	pid = find_pid_by_name(name);
	rc = kill(pid, signal);
	DIE(rc < 0, "kill");
}

static void wait_for_signal(int signal)
{
	sigset_t pending_set, wait_set;

	sigemptyset(&wait_set);
	sigaddset(&wait_set, signal);

	while (1) {
		int ret_signal;
		sigpending(&pending_set);
		if (sigismember(&pending_set, signal) == 0) {
			sigwait(&wait_set, &ret_signal);
			if (ret_signal == signal)
				break;
		}
	}
}

int main(void)
{
	block_signal(SIG);

	printf("%s\n", messages[0]);
	send_signal_to_process_by_name(SIG, "proc_sig_second");

	wait_for_signal(SIG);
	printf("%s\n", messages[2]);

	return 0;
}

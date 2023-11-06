// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>

#include "utils.h"
#include "access_counter.h"

struct page_info {
	int prot;
	void *start;
};

unsigned long counter;

#define MAX_PAGES	16
static struct page_info pages[MAX_PAGES];
static size_t num_pages;

/* This is useful for filling the contents when execution rights are provided. */
static void do_nothing(void)
{
}

/*
 * The actual SIGSEVG handler.
 */
static void access_handler(int signum, siginfo_t *si, void *arg)
{
	long page_size = sysconf(_SC_PAGESIZE);
	void *start;
	int rc;
	unsigned int i;

	log_debug("Enter handler");

	counter++;

	if (signum != SIGSEGV) {
		fprintf(stderr, "Unable to handle signal %d (%s)\n", signum, strsignal(signum));
		return;
	}

	/* TODO 2: Obtain page strart address in start variable. */
	start = (void *) ((unsigned long) si->si_addr & ~0xFFFUL);
	log_debug("start: %p", start);

	for (i = 0; i < num_pages; i++)
		if (pages[i].start == start)
			break;

	if (i >= num_pages && i < MAX_PAGES) {
		pages[i].start = start;
		pages[i].prot = PROT_NONE;
		num_pages += 1;
	}

	log_debug("i = %u", i);

	/* TODO 21: Update page proctections with mprotect(). */
	switch (pages[i].prot) {
	case PROT_NONE:
		rc = mprotect(start, page_size, PROT_READ);
		DIE(rc < 0, "mprotect");
		pages[i].prot = PROT_READ;
		break;
	case PROT_READ:
		rc = mprotect(start, page_size, PROT_READ | PROT_WRITE);
		DIE(rc < 0, "mprotect");
		pages[i].prot = PROT_WRITE;
		break;
	case PROT_WRITE:
		rc = mprotect(start, page_size, PROT_READ | PROT_WRITE | PROT_EXEC);
		DIE(rc < 0, "mprotect");
		/* Optimistically copy 64 bytes of code. Should be more than enough. */
		memcpy(start, do_nothing, 64);
		pages[i].prot = PROT_EXEC;
		break;
	default:
		break;
	}
}

void register_sigsegv_handler(void)
{
	struct sigaction sa;
	int rc;

	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = access_handler;
	sa.sa_flags = SA_SIGINFO;

	rc = sigaction(SIGSEGV, &sa, NULL);
	DIE(rc < 0, "sigaction");
}

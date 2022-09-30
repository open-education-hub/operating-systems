/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Test case for common files: Makefile, logging, DIE, ERR macros.
 */

#include <stdio.h>
#include "log.h"
#include "utils.h"

int main(void)
{
	FILE *f;
	FILE *logf;

	/* Open log file. */
	logf = fopen("open.log", "w");
	DIE(logf == NULL, "fopen");

	/* Configure logging. */
	log_set_level(LOG_INFO);
	log_add_fp(logf, LOG_TRACE);

	/* Do logging. */
	log_trace("trace");
	log_debug("debug");
	log_info("info");
	log_warn("warn");
	log_error("emerg");
	log_fatal("fatal");

	/* Print error when opening file. */
	f = fopen("/a/b/c/d.txt", "r");
	ERR(f == NULL, "fopen");

	/* Print error and exit with error when opening file. */
	f = fopen("/e/f/g/h.txt", "r");
	DIE(f == NULL, "fopen");

	return 0;
}

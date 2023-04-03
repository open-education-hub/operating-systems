// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>

#include "./parser.h"

#ifdef UNICODE
#  error "Unicode not supported in this source file!"
#endif

#define PROMPT_STRING	"> "
#define MAX_CMD_LEN		1024


void parse_error(const char *str, const int where)
{
	fprintf(stderr, "Parse error near %d: %s\n", where, str);
}


int main(void)
{
	char line[MAX_CMD_LEN];
	command_t *root = NULL;

	printf(PROMPT_STRING); fflush(stdout);
	if (fgets(line, sizeof(line), stdin) == NULL) {
		fprintf(stderr, "End of file!\n");
		return EXIT_SUCCESS;
	}

	/* We might have not read the entire line... */
	if (parse_line(line, &root)) {
		printf("Command successfully read!\n");
		if (root == NULL) {
			printf("Command is empty!\n");
		} else {
			/* Root points to a valid and usable command tree. */
			printf("Starting with command root...\n");
		}
	} else {
		/* There was an error parsing the command. */
		fprintf(stderr, "Error while parsing command!\n");
	}

	free_parse_memory();

	return EXIT_SUCCESS;
}

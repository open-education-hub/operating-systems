// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/parser/parser.h"
#include "cmd.h"
#include "utils.h"

#define PROMPT             "> "
#define CHUNK_SIZE         1024


void parse_error(const char *str, const int where)
{
	fprintf(stderr, "Parse error near %d: %s\n", where, str);
}

/**
 * Readline from mini-shell.
 */
static char *read_line(void)
{
	char *line = NULL;
	int line_length = 0;

	char chunk[CHUNK_SIZE];
	int chunk_length;

	char *rc;

	int endline = 0;

	while (!endline) {
		rc = fgets(chunk, CHUNK_SIZE, stdin);
		if (rc == NULL)
			break;

		chunk_length = strlen(chunk);
		if (chunk[chunk_length - 1] == '\n') {
			if (chunk_length > 1 && chunk[chunk_length - 2] == '\r')
				/* Windows */
				chunk[chunk_length - 2] = 0;
			else
				chunk[chunk_length - 1] = 0;
			endline = 1;
		}

		line = realloc(line, line_length + CHUNK_SIZE);
		DIE(line == NULL, "Error allocating command line");

		line[line_length] = '\0';
		strcat(line, chunk);

		line_length += CHUNK_SIZE;
	}

	return line;
}

static void start_shell(void)
{
	char *line;
	command_t *root;

	int ret;

	for (;;) {
		printf(PROMPT);
		fflush(stdout);
		ret = 0;

		root = NULL;
		line = read_line();
		if (line == NULL)
			return;
		parse_line(line, &root);

		if (root != NULL)
			ret = parse_command(root, 0, NULL);

		free_parse_memory();
		free(line);

		if (ret == SHELL_EXIT)
			break;
	}
}

int main(void)
{
	start_shell();

	return EXIT_SUCCESS;
}

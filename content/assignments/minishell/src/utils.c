// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"

/**
 * Concatenate parts of the word to obtain the command.
 */
char *get_word(word_t *s)
{
	char *string = NULL;
	int string_length = 0;

	const char *substring = NULL;
	int substring_length = 0;

	while (s != NULL) {
		if (s->expand == true) {
			substring = getenv(s->string);

			/* Prevents strlen from failing. */
			if (substring == NULL)
				substring = "";
		} else {
			substring = s->string;
		}

		substring_length = strlen(substring);

		string = realloc(string, string_length + substring_length + 1);
		DIE(string == NULL, "Error allocating word string.");

		string[string_length] = '\0';
		strcat(string, substring);

		string_length += substring_length;

		s = s->next_part;
	}

	return string;
}

/**
 * Concatenate command arguments in a NULL terminated list in order to pass
 * them directly to execv.
 */
char **get_argv(simple_command_t *command, int *size)
{
	char **argv;
	int argc;

	word_t *param;

	argc = 1;

	/* Get parameters number. */
	param = command->params;
	while (param != NULL) {
		param = param->next_word;
		argc++;
	}

	argv = calloc(argc + 1, sizeof(char *));
	DIE(argv == NULL, "Error allocating argv.");

	argv[0] = get_word(command->verb);
	DIE(argv[0] == NULL, "Error retrieving word.");

	param = command->params;
	argc = 1;
	while (param != NULL) {
		argv[argc] = get_word(param);
		DIE(argv[argc] == NULL, "Error retrieving word.");

		param = param->next_word;
		argc++;
	}

	*size = argc;

	return argv;
}

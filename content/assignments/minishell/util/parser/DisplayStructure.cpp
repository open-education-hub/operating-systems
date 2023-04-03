// SPDX-License-Identifier: BSD-3-Clause

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cassert>
#include "./parser.h"

#ifdef UNICODE
#  error "Unicode not supported in this source file!"
#endif

const int indent = 4;

void parse_error(const char * str, const int where)
{
	fprintf(stderr, "Parse error near %d: %s\n", where, str);
}

static void displayWord(word_t * w)
{
	assert(w != NULL);
	word_t * crt = w;

	while (crt != NULL) {
		if (crt->expand)
			std::cout << "expand(";
		std::cout << "'" << crt->string << "'";
		if (crt->expand)
			std::cout << ")";

		crt = crt->next_part;
		if (crt != NULL) {
			std::cout << ";    ";
			assert(crt->next_word == NULL);
		}
	}

	std::cout << std::endl;
}


static void displayList(word_t * w, int level)
{
	assert(w != NULL);
	word_t * crt = w;

	while (crt != NULL) {
		std::cout << std::setw(2 * indent * level) << "";
		displayWord(crt);
		crt = crt->next_word;
	}
}


static void displaySimple(simple_command_t * s, int level, command_t * father)
{
	assert(s != NULL);
	assert(father == s->up);

	std::cout << std::setw(2 * indent * level) << "" << "simple_command_t (" << std::endl;

	std::cout << std::setw(2 * indent * level + indent) << "" << "verb (" << std::endl;
	displayList(s->verb, level + 1);
	assert(s->verb->next_word == NULL);
	std::cout << std::setw(2 * indent * level + indent) << "" << ")" << std::endl;

	if (s->params != NULL) {
		std::cout << std::setw(2 * indent * level + indent) << "" << "params (" << std::endl;
		displayList(s->params, level + 1);
		std::cout << std::setw(2 * indent * level + indent) << "" << ")" << std::endl;
	}

	if (s->in != NULL) {
		std::cout << std::setw(2 * indent * level + indent) << "" << "in (" << std::endl;
		displayList(s->in, level + 1);
		std::cout << std::setw(2 * indent * level + indent) << "" << ")" << std::endl;
	}

	if (s->out != NULL) {
		std::cout << std::setw(2 * indent * level + indent) << "" << "out (" << std::endl;
		displayList(s->out, level + 1);
		if (s->io_flags & IO_OUT_APPEND)
			std::cout << std::setw(2 * indent * (level+1)) << "" << "APPEND" << std::endl;
		std::cout << std::setw(2 * indent * level + indent) << "" << ")" << std::endl;
	}

	if (s->err != NULL) {
		std::cout << std::setw(2 * indent * level + indent) << "" << "err (" << std::endl;
		displayList(s->err, level + 1);
		if (s->io_flags & IO_ERR_APPEND)
			std::cout << std::setw(2 * indent * (level+1)) << "" << "APPEND" << std::endl;
		std::cout << std::setw(2 * indent * level + indent) << "" << ")" << std::endl;
	}

	std::cout << std::setw(2 * indent * level) << "" << ")" << std::endl;
}


static void displayCommand(command_t * c, int level, command_t * father)
{
	assert(c != NULL);
	assert(c->up == father);

	std::cout << std::setw(2 * indent * level) << "" << "command_t (" << std::endl;
	if (c->op == OP_NONE) {
		assert(c->cmd1 == NULL);
		assert(c->cmd2 == NULL);
		std::cout << std::setw(2 * indent * level + indent) << "" << "scmd (" << std::endl;
		displaySimple(c->scmd, level + 1, c);
		std::cout << std::setw(2 * indent * level + indent) << "" << ")" << std::endl;
	} else {
		assert(c->scmd == NULL);
		std::cout << std::setw(2 * indent * level + indent) << "" << "op == ";

		switch (c->op) {
		case OP_SEQUENTIAL:
			std::cout << "OP_SEQUENTIAL";
			break;
		case OP_PARALLEL:
			std::cout << "OP_PARALLEL";
			break;
		case OP_CONDITIONAL_ZERO:
			std::cout << "OP_CONDITIONAL_ZERO";
			break;
		case OP_CONDITIONAL_NZERO:
			std::cout << "OP_CONDITIONAL_NZERO";
			break;
		case OP_PIPE:
			std::cout << "OP_PIPE";
			break;
		default:
			assert(false);
		}

		std::cout << std::endl;
		std::cout << std::setw(2 * indent * level + indent) << "" << "cmd1 (" << std::endl;
		displayCommand(c->cmd1, level + 1, c);
		std::cout << std::setw(2 * indent * level + indent) << "" << ")" << std::endl;
		std::cout << std::setw(2 * indent * level + indent) << "" << "cmd2 (" << std::endl;
		displayCommand(c->cmd2, level + 1, c);
		std::cout << std::setw(2 * indent * level + indent) << "" << ")" << std::endl;
	}

	std::cout << std::setw(2 * indent * level) << "" << ")" << std::endl;
}


int main(void)
{
	for (;;) {
		std::cout << "> ";

		std::string line;
		getline(std::cin, line);
		if ((line.length() == 0) && !std::cin.good()) {
			// end of file reached
			std::cerr << "End of file!" << std::endl;
			return EXIT_SUCCESS;
		}

		command_t* root = NULL;
		std::cout << line << std::endl;

		if (parse_line(line.c_str(), &root)) {
			std::cout << "Command successfully read!" << std::endl;
			if (root == NULL) {
				std::cout << "Command is empty!" << std::endl;
			} else {
				// Root points to a valid command tree that we can use
				displayCommand(root, 0, NULL);
			}
		}	else {
			// There was an error parsing the command
			std::cout << "Error parsing!" << std::endl;
		}

		std::cout << std::endl << std::endl;
		free_parse_memory();
	}
}

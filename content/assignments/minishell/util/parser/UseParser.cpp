// SPDX-License-Identifier: BSD-3-Clause

#include <iostream>
#include <string>
#include <cstdlib>
#include "./parser.h"

#ifdef UNICODE
#  error "Unicode not supported in this source file!"
#endif

#define PROMPT_STRING	"> "

void parse_error(const char * str, const int where)
{
	std::cerr << "Parse error near " << where << ": " << str << std::endl;
}

int main()
{
	std::cout << PROMPT_STRING;

	std::string line;
	getline(std::cin, line);
	if ((line.length() == 0) && !std::cin.good()) {
		// end of file reached
		std::cerr << "End of file!" << std::endl;
		return EXIT_SUCCESS;
	}

	command_t* root = NULL;
	if (parse_line(line.c_str(), &root)) {
		std::cout << "Command successfully read!" << std::endl;
		if (root == NULL) {
			std::cout << "Command is empty!" << std::endl;
		} else {
			//root points to a valid command tree that we can use
		}
	} else {
		//there was an error parsing the command
	}
	free_parse_memory();

	return EXIT_SUCCESS;
}

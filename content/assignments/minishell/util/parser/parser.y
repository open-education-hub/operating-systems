%defines
%locations
%{


#ifdef _WIN32
#  ifndef WIN32
#    define WIN32
#  endif
#endif


#ifdef __cplusplus

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>

using namespace std;

#else

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#endif


#define __PARSER_H_INTERNAL_INCLUDE
#include "parser.h"


static GenericPointer * globalAllocMem = NULL;
static size_t globalAllocCount = 0;
static size_t globalAllocSize  = 0;
static bool needsFree = false;
static command_t * command_root = NULL;


void yyerror(const char* str);


static void ensureSize(size_t newSize)
{
	GenericPointer * newPtr;
	assert(newSize > 0);

	if (globalAllocSize == 0) {
		assert(globalAllocMem == NULL);
		globalAllocSize = newSize;
		globalAllocMem = (GenericPointer *)malloc(sizeof(GenericPointer) * globalAllocSize);
		if (globalAllocMem == NULL) {
			fprintf(stderr, "malloc() failed\n");
			exit(EXIT_FAILURE);
		}

		return;
	}

	assert(globalAllocMem != NULL);
	if (globalAllocSize >= newSize) {
		return;
	}

	globalAllocSize += newSize;
	newPtr = (GenericPointer *)realloc((void *)globalAllocMem, sizeof(GenericPointer) * globalAllocSize);
	if (newPtr == NULL) {
		fprintf(stderr, "realloc() failed\n");
		exit(EXIT_FAILURE);
	}

	globalAllocMem = newPtr;
}


void pointerToMallocMemory(const void * ptr)
{
	if (ptr == NULL) {
		fprintf(stderr, "malloc() failed\n");
		exit(EXIT_FAILURE);
	}

	ensureSize(globalAllocCount + 1);
	globalAllocMem[globalAllocCount++] = (GenericPointer)ptr;
}


static simple_command_t * bind_parts(word_t * exe_name, word_t * params, redirect_t red)
{
	simple_command_t * s = (simple_command_t *) malloc(sizeof(simple_command_t));
	pointerToMallocMemory(s);

	memset(s, 0, sizeof(*s));
	assert(exe_name != NULL);
	assert(exe_name->next_word == NULL);
	s->verb = exe_name;
	s->params = params;
	s->in = red.red_i;
	s->out = red.red_o;
	s->err = red.red_e;
	s->io_flags = red.red_flags;
	s->up = NULL;
	s->aux = NULL;
	return s;
}


static command_t * new_command(simple_command_t * scmd)
{
	command_t * c = (command_t *) malloc(sizeof(command_t));

	if (c == NULL) {
		fprintf(stderr, "malloc() failed\n");
		exit(EXIT_FAILURE);
	}
	pointerToMallocMemory(c);

	memset(c, 0, sizeof(*c));
	c->up = c->cmd1 = c->cmd2 = NULL;
	c->op = OP_NONE;
	assert(scmd != NULL);
	c->scmd = scmd;
	scmd->up = c;
	c->aux = NULL;
	return c;
}


static command_t * bind_commands(command_t * cmd1, command_t * cmd2, operator_t op)
{
	command_t * c = (command_t *) malloc(sizeof(command_t));
	pointerToMallocMemory(c);

	memset(c, 0, sizeof(*c));
	c->up = NULL;
	assert(cmd1 != NULL);
	assert(cmd1->up == NULL);
	c->cmd1 = cmd1;
	cmd1->up = c;
	assert(cmd2 != NULL);
	assert(cmd2->up == NULL);
	assert(cmd1 != cmd2);
	c->cmd2 = cmd2;
	cmd2->up = c;
	assert((op > OP_NONE) && (op < OP_DUMMY));
	c->op = op;
	c->scmd = NULL;
	c->aux = NULL;

	return c;
}


static word_t * new_word(const char * str, bool expand)
{
	word_t * w = (word_t *) malloc(sizeof(word_t));
	pointerToMallocMemory(w);

	memset(w, 0, sizeof(*w));
	assert(str != NULL);
	w->string = str;
	w->expand = expand;
	w->next_part = NULL;
	w->next_word = NULL;

	return w;
}


static word_t * add_part_to_word(word_t * w, word_t * lst)
{
	word_t * crt = lst;
	assert(lst != NULL);
	assert(w != NULL);

	/*
	 we could insert at the beginnig and then invert the list
	 but this would make the code a bit more complicated
	 thus, we assume we have small lists and O(n*n) is acceptable
	*/

	while (crt->next_part != NULL) {
		crt = crt->next_part;
		assert((crt == NULL) || (crt->next_word == NULL));
	}

	crt->next_part = w;
	assert(w->next_part == NULL);
	assert(w->next_word == NULL);

	return lst;
}


static word_t * add_word_to_list(word_t * w, word_t * lst)
{
	word_t * crt = lst;
	assert(w != NULL);

	if (crt == NULL) {
		assert(w->next_word == NULL);
		return w;
	}
	assert(lst != NULL);

	/*
	 same as above
	*/
	while (crt->next_word != NULL) {
		crt = crt->next_word;
	}

	crt->next_word = w;
	assert(w->next_word == NULL);

	return lst;
}


%}

%union {
	command_t * command_un;
	const char * string_un;
	redirect_t redirect_un;
	simple_command_t * simple_command_un;
	word_t * exe_un;
	word_t * params_un;
	word_t * word_un;
}


%token NOT_ACCEPTED_CHAR INVALID_ENVIRONMENT_VAR UNEXPECTED_EOF CHARS_AFTER_EOL
%token END_OF_FILE END_OF_LINE BLANK
%token REDIRECT_OE REDIRECT_O REDIRECT_E INDIRECT
%token REDIRECT_APPEND_E REDIRECT_APPEND_O
%token <string_un> WORD
%token <string_un> ENV_VAR

%left SEQUENTIAL
%left PARALLEL
%left CONDITIONAL_NZERO CONDITIONAL_ZERO
%left PIPE

%type <command_un> command
%type <exe_un> exe_name
%type <params_un> params
%type <redirect_un> redirect
%type <simple_command_un> simple_command
%type <word_un> word

%start command_tree

%%

command_tree:

	  command END_OF_LINE {
		command_root = $1;
		YYACCEPT;
	}

	| command END_OF_FILE {
		command_root = $1;
		YYACCEPT;
	}

	| END_OF_LINE {
		command_root = NULL;
		YYACCEPT;
	}

	| END_OF_FILE {
		command_root = NULL;
		YYACCEPT;
	}

	| BLANK END_OF_LINE {
		command_root = NULL;
		YYACCEPT;
	}

	| BLANK END_OF_FILE {
		command_root = NULL;
		YYACCEPT;
	}

	;

command:

	  simple_command {
		$$ = new_command($1);
	}

	| command SEQUENTIAL command {
		$$ = bind_commands($1, $3, OP_SEQUENTIAL);
	}

	| command PARALLEL command {
		$$ = bind_commands($1, $3, OP_PARALLEL);
	}

	| command CONDITIONAL_ZERO command {
		$$ = bind_commands($1, $3, OP_CONDITIONAL_ZERO);
	}

	| command CONDITIONAL_NZERO command {
		$$ = bind_commands($1, $3, OP_CONDITIONAL_NZERO);
	}

	| command PIPE command {
		$$ = bind_commands($1, $3, OP_PIPE);
	}

	;

simple_command:

	  exe_name BLANK params redirect {
		$$ = bind_parts($1, $3, $4);
	}

	| exe_name BLANK params BLANK redirect {
		$$ = bind_parts($1, $3, $5);
	}

	| exe_name redirect {
		$$ = bind_parts($1, NULL, $2);
	}

	| exe_name BLANK redirect {
		$$ = bind_parts($1, NULL, $3);
	}

	;

exe_name:

	  word {
		$$ = $1;
	}

	| BLANK word {
		$$ = $2;
	}

	;

params:

	  params BLANK word {
		$$ = add_word_to_list($3, $1);
		assert($$ == $1);
	}

	| word {
		$$ = $1;
	}
	;

redirect:

	  { /* empty */
		$$.red_o = NULL;
		$$.red_i = NULL;
		$$.red_e = NULL;
		$$.red_flags = IO_REGULAR;
	}

	| redirect REDIRECT_OE word {
		$1.red_o = add_word_to_list($3, $1.red_o);
		$1.red_e = add_word_to_list($3, $1.red_e);
		$$ = $1;
	}

	| redirect REDIRECT_E word {
		$1.red_e = add_word_to_list($3, $1.red_e);
		$$ = $1;
	}

	| redirect REDIRECT_O word {
		$1.red_o = add_word_to_list($3, $1.red_o);
		$$ = $1;
	}

	| redirect REDIRECT_APPEND_E word {
		$1.red_e = add_word_to_list($3, $1.red_e);
		$1.red_flags |= IO_ERR_APPEND;
		$$ = $1;
	}

	| redirect REDIRECT_APPEND_O word {
		$1.red_o = add_word_to_list($3, $1.red_o);
		$1.red_flags |= IO_OUT_APPEND;
		$$ = $1;
	}

	| redirect INDIRECT word {
		$1.red_i = add_word_to_list($3, $1.red_i);
		$$ = $1;
	}

	| redirect REDIRECT_OE word BLANK {
		$1.red_o = add_word_to_list($3, $1.red_o);
		$1.red_e = add_word_to_list($3, $1.red_e);
		$$ = $1;
	}

	| redirect REDIRECT_E word BLANK {
		$1.red_e = add_word_to_list($3, $1.red_e);
		$$ = $1;
	}

	| redirect REDIRECT_O word BLANK {
		$1.red_o = add_word_to_list($3, $1.red_o);
		$$ = $1;
	}

	| redirect REDIRECT_APPEND_E word BLANK {
		$1.red_e = add_word_to_list($3, $1.red_e);
		$1.red_flags |= IO_ERR_APPEND;
		$$ = $1;
	}

	| redirect REDIRECT_APPEND_O word BLANK {
		$1.red_o = add_word_to_list($3, $1.red_o);
		$1.red_flags |= IO_OUT_APPEND;
		$$ = $1;
	}

	| redirect INDIRECT word BLANK {
		$1.red_i = add_word_to_list($3, $1.red_i);
		$$ = $1;
	}

	| redirect REDIRECT_OE BLANK word {
		$1.red_o = add_word_to_list($4, $1.red_o);
		$1.red_e = add_word_to_list($4, $1.red_e);
		$$ = $1;
	}

	| redirect REDIRECT_E BLANK word {
		$1.red_e = add_word_to_list($4, $1.red_e);
		$$ = $1;
	}

	| redirect REDIRECT_O BLANK word {
		$1.red_o = add_word_to_list($4, $1.red_o);
		$$ = $1;
	}

	| redirect REDIRECT_APPEND_E BLANK word {
		$1.red_e = add_word_to_list($4, $1.red_e);
		$1.red_flags |= IO_ERR_APPEND;
		$$ = $1;
	}

	| redirect REDIRECT_APPEND_O BLANK word {
		$1.red_o = add_word_to_list($4, $1.red_o);
		$1.red_flags |= IO_OUT_APPEND;
		$$ = $1;
	}

	| redirect INDIRECT BLANK word {
		$1.red_i = add_word_to_list($4, $1.red_i);
		$$ = $1;
	}
	| redirect REDIRECT_OE BLANK word BLANK {
		$1.red_o = add_word_to_list($4, $1.red_o);
		$1.red_e = add_word_to_list($4, $1.red_e);
		$$ = $1;
	}

	| redirect REDIRECT_E BLANK word BLANK {
		$1.red_e = add_word_to_list($4, $1.red_e);
		$$ = $1;
	}

	| redirect REDIRECT_O BLANK word BLANK {
		$1.red_o = add_word_to_list($4, $1.red_o);
		$$ = $1;
	}

	| redirect REDIRECT_APPEND_O BLANK word BLANK {
		$1.red_o = add_word_to_list($4, $1.red_o);
		$1.red_flags |= IO_OUT_APPEND;
		$$ = $1;
	}

	| redirect REDIRECT_APPEND_E BLANK word BLANK {
		$1.red_e = add_word_to_list($4, $1.red_e);
		$1.red_flags |= IO_ERR_APPEND;
		$$ = $1;
	}

	| redirect INDIRECT BLANK word BLANK {
		$1.red_i = add_word_to_list($4, $1.red_i);
		$$ = $1;
	}

	;

word:

	  word WORD {
		$$ = add_part_to_word(new_word($2, false), $1);
	}

	| word ENV_VAR {
		$$ = add_part_to_word(new_word($2, true), $1);
	}

	| WORD {
		$$ = new_word($1, false);
	}

	| ENV_VAR {
		$$ = new_word($1, true);
	}

	;
%%


bool parse_line(const char * line, command_t ** root)
{
	if (*root != NULL) {
		/* see the comment in parser.h */
		assert(false);
		return false;
	}

	if (line == NULL) {
		/* see the comment in parser.h */
		assert(false);
		return false;
	}

	free_parse_memory();
	globalParseAnotherString(line);
	needsFree = true;
	command_root = NULL;

	yylloc.first_line = yylloc.last_line = 1;
	yylloc.first_column = yylloc.last_column = 0;

	if (yyparse() != 0) {
		/* yyparse failed */
		return false;
	}

	*root = command_root;

	return true;
}


void free_parse_memory()
{
	if (needsFree) {
		globalEndParsing();
		while (globalAllocCount != 0) {
			globalAllocCount--;
			assert(globalAllocMem[globalAllocCount] != NULL);
			free(globalAllocMem[globalAllocCount]);
			globalAllocMem[globalAllocCount] = NULL;
		}

		if (globalAllocMem != NULL) {
			free((void *)globalAllocMem);
			globalAllocMem = NULL;
		}

		globalAllocSize = 0;
		needsFree = false;
	}
}


void yyerror(const char* str)
{
	parse_error(str, yylloc.first_column);
}

/* SPDX-License-Identifier: BSD-3-Clause */


#ifndef __PARSER_H
#define __PARSER_H

/*
 * Include this header to use the parser.

 * For an example of the usage see
 * CUseParser.c
 * UseParser.cpp

 * For an example of the build run make and see the commands it executes
 * (see README for details)

 * If you want to see the structure of the generated parse tree, run
 * ./DisplayStructure
 */



#ifdef __cplusplus
#else
/*
 * Use this to simulate the bool type in C++; e.g.:

 * bool flag = false;
 * if (flag) ...
 * else      ...
 *
 */
typedef enum {
	false,
	true
} bool;
#endif


/*
 * String literal list

 * String literals can be made up of multiple strings
 * (next_part points to the next part of a string or
 * is NULL if there are no more parts)

 * Some parts might need environment variable expansion (expand == true);
 * if that is the case, "string" points to the environment variable name

 * The next string literal is pointed to by next_word
 * (NULL if there are no more list elements)

 * The parser guarantees that '=' will be a single part of a string
 * (e.g. "name=value" will contain three parts: "name" "=" "value"
 * (except for quoted strings in the original command line))
 * this can ease implementing an internal command similar to export,
 * although the parser does not provide full functionality for this.
 * You are not required to implement export.

 * To tell if a string literal represents an internal command, first
 * concatenate all its parts (expanding them if necessary) and then
 * compare the result using string comparison.
 */

typedef struct word_t {
	const char *string;
	bool expand;
	struct word_t *next_part;
	struct word_t *next_word;
} word_t;


/*
 * Describes a simple command

 * aux can be used to point to additional information you might need;
 * freeing the memory aux points to is your responsibility. aux will
 * be initialized to NULL. Do not modify these structures, please use
 * aux.

 * verb points to a single string literal (possibly made up of parts)
 * that is the executable name or the internal command name.

 * params points to a list of parameters (possibly none) in the order
 * they were entered in the command line.

 * in out and err point to the names of the redirections for the command;
 * they can point to a single literal, no literal (the command does not
 * have that redirection) or multiple literals (the user entered multiple
 * redirections for a command; e.g. cat >out1 >out2). You can handle the
 * latter as you wish (e.g. only consider the first redirection). Within
 * any of these lists, the literals are in the original order.

 * io_flags is used to specify special modes for redirection (e.g. appending)

 * Some string literals can be found in both the out list and the err list
 * (those entered as "command &> out").

 * up points to the command_t structure that points to this simple_command_t
 * (up != NULL)
 */

#define IO_REGULAR	0x00
#define IO_OUT_APPEND	0x01
#define IO_ERR_APPEND	0x02

typedef struct {
	word_t *verb;
	word_t *params;
	word_t *in;
	word_t *out;
	word_t *err;
	int io_flags;
	struct command_t *up;
	void *aux;
} simple_command_t;


/*
 * Operators

 * OP_NONE means no operator
 * (the scmd field points to a simple command and cmd1 == cmd2 == NULL)

 * The rest of the operators mean scmd == NULL

 * OP_DUMMY is a dummy value that can be used to count the number of operators
 */

typedef enum {
	OP_NONE,
	OP_SEQUENTIAL,
	OP_PARALLEL,
	OP_CONDITIONAL_ZERO,
	OP_CONDITIONAL_NZERO,
	OP_PIPE,
	OP_DUMMY
} operator_t;


/*
 * Describes a command tree (a node of the parse tree)

 *  if (op == OP_NONE)
      scmd != NULL
      cmd1 == cmd2 == NULL
      scmd points to a command to be executed
 *  else
      scmd == NULL
      cmd1 != NULL
      cmd2 != NULL
      cmd1 op cmd2 must be executed, according to the rules for op

 * You can use aux the same way as for simple_command_t

 * up points to the command_t that points to this structure
 * (the father of the current node in the parse tree)
 * The root of the tree has up == NULL

 * The parsed expressions do not contain parantheses, this means that
 * the following holds:
 * for any op_lower that has a lower priority than op, there is no
 * parent in the tree with op == op_lower
 * In particular, if op == OP_PIPE descendants
 * can only have OP_PIPE or OP_NONE
 */

typedef struct command_t {
	struct command_t *up;
	struct command_t *cmd1;
	struct command_t *cmd2;
	operator_t op;
	simple_command_t *scmd;
	void *aux;
} command_t;


#ifdef __cplusplus
extern "C"
{
#endif


/*
 * You must define this function; it will be called by the parser
 * when a parse error occurs; str describes the error (not a useful
 * description) and where points to some location before the error
 * was discovered (the character number, starting at 0)
 */

void parse_error(const char *str, const int where);


/*
 * Call this to parse a line

 * line must point to a string containig a single line
 * The line must end with "\r\n\0" or "\n\0" or "\0"
 * (*root) must point to NULL ((*root) == NULL)

 * parse_line returns true if there was no error parsing the line
 * and false if there was an error parsing or the arguments were invalid

 * if parse_line returns true:
 *   if line was empty (or contained just blanks) (*root) is NULL
 *   else (*root) points to the root of the parse tree
 */

bool parse_line(const char *line, command_t **root);


/*
 * Should be called to free the parse tree
 * call this even if parse_line() returned false
 */

void free_parse_memory(void);

#ifdef __cplusplus
}
#endif


#ifdef __PARSER_H_INTERNAL_INCLUDE

/*
 * Parser and lexer common internal stuff
 */

typedef void *GenericPointer;

typedef struct {
	word_t *red_i;
	word_t *red_o;
	word_t *red_e;
	int red_flags;
} redirect_t;


#ifdef __cplusplus
extern "C"
{
#endif

void pointerToMallocMemory(const void *ptr);
int yylex(void);
void globalParseAnotherString(const char *str);
void globalEndParsing(void);

#ifdef __cplusplus
}
#endif

#endif

/*
 * Parser written by Maximilian Machedon, based on a previous version.
 */

#endif

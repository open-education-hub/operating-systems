%option nostdinit never-interactive nounput noinput
%{


#ifdef _WIN32
#  ifndef WIN32
#    define WIN32
#  endif
#endif

#ifdef _MSC_VER
/* Speaking of MS, they do not implement standard C;
 * YY_USE_CONST is defined only if __STDC__ is defined;
 * here is alread too late to redefine YY_USE_CONST so
 * we use pragma instead ^^.
 */
#pragma warning(disable:4090)
#endif /* _MSC_VER */

#ifdef __MINGW32_VERSION
#  ifndef _NO_OLDNAMES
#    define _NO_OLDNAMES
#  endif
#endif


#ifndef HAVE_UNISTD_H
#  define YY_NO_UNISTD_H
#endif


#ifdef __cplusplus

#include <cstdio>
#include <cstring>
#include <cassert>

using namespace std;

#else

#include <stdio.h>
#include <string.h>
#include <assert.h>

#endif

#define __PARSER_H_INTERNAL_INCLUDE
#include "parser.h"
#include "parser.tab.h"


#ifdef WIN32

#include <io.h>
#ifndef isatty
#  define isatty _isatty
#endif
#ifndef strdup
#  define strdup _strdup
#endif
#ifndef fileno
#  define fileno _fileno
#endif

#endif


#ifndef YY_SKIP_YYWRAP
#  define YY_SKIP_YYWRAP 1
#endif


int yywrap(void)
{
	return 1;
}

#define UPD_LOCATION \
	yylloc.first_column = yylloc.last_column; \
	yylloc.last_column += yyleng

%}


digit				[0-9]
letter				[a-zA-Z]
envVarName 			((_|{letter})(_|{letter}|{digit})*)
parameterValue 			(({letter}|{digit}|[\-\\+:._%?*~/,])+)
whitespace			[ \t]
newLine				(\r?\n)
substitutionCharacter		[$]
setValueCharacter		[=]
charStateAny			[']
allButCharStateAny		[^']
charStateAnyAndExpansion	["]
allButCharStateAnyAndExpansion	[^"$]
anyChar				(.|\n)
pipeChar			[|]
andChar				[&]
gtChar				[>]
gtgtChar			[>][>]
ltChar				[<]
semicolon			[;]


%s ACCEPT_ANY ACCEPT_ANY_AND_EXPANSION


%%
<INITIAL><<EOF>> {
	return END_OF_FILE;
}
<INITIAL>{newLine}{anyChar} {
	UPD_LOCATION;
	return CHARS_AFTER_EOL;
}
<INITIAL>{newLine} {
	UPD_LOCATION;
	return END_OF_LINE;
}
<INITIAL>{charStateAny} {
	UPD_LOCATION;
	BEGIN(ACCEPT_ANY);
}
<INITIAL>{charStateAnyAndExpansion} {
	UPD_LOCATION;
	BEGIN(ACCEPT_ANY_AND_EXPANSION);
}
<INITIAL>{semicolon} {
	UPD_LOCATION;
	return SEQUENTIAL;
}
<INITIAL>{pipeChar}{pipeChar} {
	UPD_LOCATION;
	return CONDITIONAL_NZERO;
}
<INITIAL>{pipeChar} {
	UPD_LOCATION;
	return PIPE;
}
<INITIAL>{andChar}{andChar} {
	UPD_LOCATION;
	return CONDITIONAL_ZERO;
}
<INITIAL>{andChar}{gtChar} {
	UPD_LOCATION;
	return REDIRECT_OE;
}
<INITIAL>{andChar} {
	UPD_LOCATION;
	return PARALLEL;
}
<INITIAL>[2]{gtgtChar} {
	UPD_LOCATION;
	return REDIRECT_APPEND_E;
}
<INITIAL>{gtgtChar} {
	UPD_LOCATION;
	return REDIRECT_APPEND_O;
}
<INITIAL>[2]{gtChar} {
	UPD_LOCATION;
	return REDIRECT_E;
}
<INITIAL>{gtChar} {
	UPD_LOCATION;
	return REDIRECT_O;
}
<INITIAL>{ltChar} {
	UPD_LOCATION;
	return INDIRECT;
}
<INITIAL>{whitespace}+ {
	UPD_LOCATION;
	return BLANK;
}
<INITIAL>{setValueCharacter} {
	UPD_LOCATION;
	yylval.string_un = strdup(yytext);
	pointerToMallocMemory(yylval.string_un);
	return WORD;
}
<INITIAL>{substitutionCharacter}{envVarName} {
	UPD_LOCATION;
	yylval.string_un = strdup(yytext + 1);
	pointerToMallocMemory(yylval.string_un);
	return ENV_VAR;
}
<INITIAL>{substitutionCharacter} {
	UPD_LOCATION;
	return INVALID_ENVIRONMENT_VAR;
}
<INITIAL>{parameterValue} {
	UPD_LOCATION;
	yylval.string_un = strdup(yytext);
	pointerToMallocMemory(yylval.string_un);
	return WORD;
}
<ACCEPT_ANY><<EOF>> {
	return UNEXPECTED_EOF;
}
<ACCEPT_ANY>{charStateAny} {
	UPD_LOCATION;
	BEGIN(INITIAL);
}
<ACCEPT_ANY>{allButCharStateAny}* {
	UPD_LOCATION;
	yylval.string_un = strdup(yytext);
	pointerToMallocMemory(yylval.string_un);
	return WORD;
}
<ACCEPT_ANY_AND_EXPANSION><<EOF>> {
	return UNEXPECTED_EOF;
}
<ACCEPT_ANY_AND_EXPANSION>{charStateAnyAndExpansion} {
	UPD_LOCATION;
	BEGIN(INITIAL);
}
<ACCEPT_ANY_AND_EXPANSION>{substitutionCharacter}{envVarName} {
	UPD_LOCATION;
	yylval.string_un = strdup(yytext + 1);
	pointerToMallocMemory(yylval.string_un);
	return ENV_VAR;
}
<ACCEPT_ANY_AND_EXPANSION>{substitutionCharacter} {
	UPD_LOCATION;
	return INVALID_ENVIRONMENT_VAR;
}
<ACCEPT_ANY_AND_EXPANSION>{allButCharStateAnyAndExpansion}* {
	UPD_LOCATION;
	yylval.string_un = strdup(yytext);
	pointerToMallocMemory(yylval.string_un);
	return WORD;
}
{anyChar} {
	UPD_LOCATION;
	return NOT_ACCEPTED_CHAR;
}
%%


YY_BUFFER_STATE myState;
bool haveOneBufferState = false;


void globalParseAnotherString(const char * str)
{
	globalEndParsing();
	myState = yy_scan_string(str);
	BEGIN(INITIAL);
	/*
	 * Actually i don't know how this should be done, but the
	 * above seems to work OK
	 */
	haveOneBufferState = true;
}


void globalEndParsing()
{
	if (haveOneBufferState) {
		yylex_destroy();
		haveOneBufferState = false;
	}
}

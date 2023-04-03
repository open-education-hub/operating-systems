# Parser

The parser is made using [Bison](http://www.gnu.org/software/bison/) and [Flex](http://flex.sourceforge.net/).

The parser is used to parse the commands entered by the user, stored in structure `command_t`.

This structure is defined in the file `parser.h` and encapsulates a tree representation of the command.

You can use `DisplayStructure.cpp` to display the structure using various [tests](#tests).

Also you can use `CUseParser.c` or `UseParser.cpp` to see how to use the parser in C or C++ and print the structure of the command.

## Compile

Run the following commands in the root of parser directory:

```console
student@os:/.../minishell/util/parser$ make
```

## Usage

The parser is represented by two files:

* `parser.y` - implementation of the parser
* `parser.l` - implementation of the lexer

### Build process

The Makefile first generates the files `parser.yy.c` and `parser.tab.c` from `parser.y` and `parser.l`.
After that, it compiles the files `parser.yy.c` and `parser.tab.c` to generate the object files `parser.yy.o` and `parser.tab.o`.
To use the parser, you need to link the object files `parser.yy.o` and `parser.tab.o` with your program.

### Example

* `CUseParser.c` - example of using the parser in C
* `UseParser.cpp` - example of using the parser in C++
* `DisplayStructure.cpp` - reads multiple commands and displays the structure of the resulting tree

### Tests

More tests can be found in the `tests` directory:

```console
student@os:/.../minishell/util/parser$ cd tests

student@os:/.../minishell/util/parser/tests$ ../DisplayStructure &>small_tests.out <small_tests.txt

student@os:/.../minishell/util/parser/tests$ cat small_tests.out
> mkdir tmp
Command successfully read!
command_t (
    scmd (
        simple_command_t (
            verb (
                'mkdir'
            )
            params (
                'tmp'
            )
        )
    )
)

> cd tmp
Command successfully read!
command_t (
    scmd (

...
student@os:/.../minishell/util/parser/tests$ ../DisplayStructure &>ugly_tests.out <ugly_tests.txt

student@os:/.../minishell/util/parser/tests$ ../DisplayStructure &>negative_tests.out <negative_tests.txt
```

#### Note

The parser will fail with an error of unknown character if you use the Linux parser (which considers the end of line as `\n`) on Windows files (end of line as `\r\n`) because at the end of the lines (returned by `getline()`) there will be a `\r` followed by `\n`.
The opposite works (Windows parser with Linux files).
The test files use the Linux convention (`\n`).

### Other information

More information about the parser can be found in the file `parser.h`.

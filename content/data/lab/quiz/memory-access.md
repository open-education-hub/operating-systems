# Modify String

## Question Text

What happens if we introduce the code `cp[2] = 't'` in the program located in the `memory-access/mem_access.c` file?

## Question Answers

- Compile time error because we are trying to modify a `const` pointer.

- Compile time error because we are trying to modify a `const` value.

+ Segmentation fault at runtime we are trying to modify read-only memory.

- Program compiles and runs succesfully.

## Feedback

The declaration `char *const cp = "ConstLeString"` actually defines 2 memory locations.
One stores a constant pointer, `cp`, whereas the other stores the actual string.
The compiler thinks that `cp` is able to modify the memory location that it points therefore it passes compilation.
But at runtime a segmentation fault is issued because we are accessing data that is stored in read-only memory.

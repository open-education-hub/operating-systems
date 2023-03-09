# ASLR

## Question Text

If we enable ASLR and run the `bo_write_practice` executable with the previously payload what vulnerabilities will we be able to still exploit?

## Question Answers

- we can still jump to the `secret_func`

- we can both still jump to the `secret_func` and overwrite the local variable

- we can jump to a library function

+ we can still overwrite the local variable

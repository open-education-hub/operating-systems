# Strcpy Buffer Overflow

## Question Text

Does any buffer overflow occur with the latest version of the program?

## Question Answers

- no, because `strcpy()` was designed to correctly handle such situations.

- no, because the string is correctly printed, i.e. no extra characters.

- we cannot know

+ yes, `strcpy()` copies the entirety of the source, including the `\0`; since the size of `dst` is 4 the null byte overwrites the least significant byte of `var`

## Feedback

Print the contents of variable `var`.

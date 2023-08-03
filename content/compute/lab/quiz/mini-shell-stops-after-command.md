# Mini-shell Stops After Command

## Question Text

Why does the `mini_shell` process stop after executing a single command?

## Question Answers

- Because of an implementation error

+ Because the `mini_shell` process doesn't exist anymore

- Because the OS sees that the command has ended and ends the `mini_shell` process as well

- Because `exec*()` syscalls also kill the caller process when the callee ends

## Feedback

When you `exec*()` any binary, the VAS current process is **replaced** by that corresponding to that binary.
So when you `exec*("ls")`, for example, the `mini_shell` process _becomes_ `ls`.
There is no more `mini_shell` past this point.
So when `ls` ends, there is no `mini_shell` process to continue its execution anymore.

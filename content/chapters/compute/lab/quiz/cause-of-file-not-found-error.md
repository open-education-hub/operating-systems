# Cause of `FileNotFoundError`

## Question Text

What causes the `FileNotFoundError` when running `support/wait-for-me/wait_for_me_processes.py`?

## Question Answers

+ The parent process attempts to open the file before the child process has had the time to create it

- There is a syntax error in the Python code

- The mode with which to open the file is not specified in the parent process

- The child process doesn't close the file

## Feedback

What you've just experienced is a **race condition**.
Race conditions are situations in which one thread uses data that may or may not have been previously modified by another thread.
Because scheduling is generally nondeterministic, this means that on some runs, the first thread may access unmodified data and modified on others.
It's impossible to say what kind of data will be used by the first thread.
In our case, the data is the file you give to the script as an argument.
If scheduling the parent process or its running time takes long enough, the file may have been created by the time the parent needs it, but we can never be sure.

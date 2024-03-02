# Digital Forensics

## Scenario

For digital forensics operations (digital evidence investigation), we want to develop an application that dumps the entire physical memory (RAM) of a modern operating system (such as Linux, Windows, macOS).
We assume there is a dedicated interface of the operating system that allows reading of physical memory for dumping.
The application can dump to a file or to standard output (for redirection to a file or network redirection).
The result is a dump with the size of the physical memory (RAM) of the system.

Answer the following questions with "True" or "False" and justify your answer.
The justification should be simple, 2-3 sentences for each answer.

## Question 1 Text

The application must be run in privileged mode, as root.

## Question 1 Answers

+ True

- False

## Question 1 Arguments

type: textbox

## Question 2 Text

During its execution, the application does not make system calls.

## Question 2 Answers

- True

+ False

## Question 2 Arguments

type: textbox

## Question 3 Text

The application will benefit from a multithreaded implementation.

## Question 3 Answers

+ True

- False

## Question 3 Arguments

type: textbox

## Question 4 Text

The memory dump will contain information about the application itself.

## Question 4 Answers

+ True

- False

## Question 4 Arguments

type: textbox

## Question 5 Text

At runtime, the application will use network sockets.

## Question 5 Answers

- True

+ False

## Question 5 Arguments

type: textbox

## Question 6 Text

Two instances of the application CANNOT run simultaneously on the same system.

## Question 6 Answers

- True

+ False

## Question 6 Arguments

type: textbox

## Question 7 Text

In its implementation, the application must use synchronization primitives.

## Question 7 Answers

- True

+ False

## Question 7 Arguments

type: textbox

## Question 8 Text

The application must be implemented in the form of a static executable.

## Question 8 Answers

- True

+ False

## Question 8 Arguments

type: textbox

## Question 9 Text

During its execution, the application uses the virtual memory mechanism.

## Question 9 Answers

+ True

- False

## Question 9 Arguments

type: textbox

## Question 10 Text

The application cannot realistically be used on a 64-bit system, only on a 32-bit system.

## Question 10 Answers

- True

+ False

## Question 10 Arguments

type: textbox

## Question 11 Text

As long as the operating system provides support, the application can work on both x86 and ARM processor architectures.

## Question 11 Answers

- True

+ False

## Question 11 Arguments

type: textbox

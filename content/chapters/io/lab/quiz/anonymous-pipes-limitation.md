# Limitation of Anonymous Pipes

## Question Text

What of the following is the largest drawback of using anonymous pipes (created with `pipe()`) for inter-process communication?

## Question Answers

- they only allow unidirectional communication

+ they only allow IPC between "related" processes (parent - child - grandchild etc.)

- if more processes use the same end of the same pipe, there may be race conditions

- a pipe only has 2 file descriptors, but some processes may need more channels to communicate

## Feedback

Out of the answers above, the only limitation that cannot be overcome by using pipes alone is the requirement for the processes using them to be related.
The parent must create the pipes so the children can inherit them.
All other downsides can be overcome by using more pipes.

The answer to this is to employ _some_ filesystem support.

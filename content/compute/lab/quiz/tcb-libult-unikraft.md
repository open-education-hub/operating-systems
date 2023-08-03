# Similarities Between the TCBs of `libult` and Unikraft

## Question Text

Which members of the TCBs in `libult` and Unikraft have similar meanings?

## Question Answers

+ `start_routine` and `entry`

- `id` and `name`

+ `context.uc_stack` and `stack`

- `arguments` and `flags`

- `has_dynamic_stack` and `detached`

+ `argument` and `arg`

- `context` and `sched`

- `context` and `tls`

+ `context` and `ctx`

+ `return_value` and `prv`

## Feedback

`start_routine` and `entry` are the functions that run in the newly created threads.
`context.uc_stack` and `stack` are pointers to the stack of the newly created threads.
`argument` and `arg` are pointers to the arguments of `start_routine` and `entry`, respectively.
`context` and `ctx` are the contexts in which the new threads run.
`return_value` and `prv` are both pointers to the values returned by the thread functions.

# Child Faults After Write

## Question Text

What causes the page faults registered by the child after the fifth step?

## Question Answers

+ The child writes data to the frames it previously shared with its parent and the copy-on-write mechanism copies and remaps them before writing said data

- Demand paging propagates the lazy allocation of pages from the parent to the child

- Creating the child process inherently duplicates some frames

- They are caused by the loader forking itself when creating the child process

- They are caused by the `bash` process forking itself when creating the child process

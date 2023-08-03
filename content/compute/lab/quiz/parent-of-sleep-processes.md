# Parent of `sleep` Processes

## Question Text

Who is the parent of the `sleep` processes?
Why?

## Question Answers

- `sleepy_creator.py` because it is the one who created them

- `bash` because it is `sleepy_creator.py`'s parent and when a process dies, its parent adopts its orphan children

+ `systemd` because this is the default process that adopts orphans

- `systemd` because it is `sleepy_creator.py`'s parent and when a process dies, its parent adopts its orphan children

## Feedback

When a process dies without waiting for the termination of all its children, those processes are now orphans.
Then the `systemd` process adopts those orphan processes by default.
On older Linux systems, it was the `init` process who adopted orphans.

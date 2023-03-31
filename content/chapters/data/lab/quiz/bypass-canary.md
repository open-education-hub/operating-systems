# Bypass Canary

## Question

If we enable ASLR, can we still exploit the `stack_protector` program?

- no, because the address of `pawned` is  going to be different for every run.

- yes, because ASLR cannot work well when the canary is activated.

+ yes, because ASLR randomizes the start address of a section, but the offsets remain the same.

- no, because the address to which `addr` points to is going to be random

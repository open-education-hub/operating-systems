extern main
extern exit
extern __libc_start_main

section .text

global _start

_start:
    mov rdi, main
    call __libc_start_main

    mov rdi, rax
    call exit

    hlt

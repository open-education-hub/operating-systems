BITS 64
    ; call getpid()
    ; rax <- 39 (__NR_write)
    mov rax, 39
    syscall

    ; call exit_group(0)
    ; rax <- 231 (__NR_exit_group)
    ; rdi <- 0 (exit status)
    mov rax, 231
    xor rdi, rdi
    syscall

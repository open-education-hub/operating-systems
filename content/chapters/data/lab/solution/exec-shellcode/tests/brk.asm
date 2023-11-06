BITS 64
    ; call brk(0)
    ; rax <- 12 (__NR_brj)
    ; rdi <- 0
    ; TODO 3: Make brk syscall.
    mov rax, 12
    xor rdi,rdi
    syscall

    ; call exit_group(0)
    ; rax <- 231 (__NR_exit_group)
    ; rdi <- 0 (exit status)
    mov rax, 231
    xor rdi, rdi
    syscall

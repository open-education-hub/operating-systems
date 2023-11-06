BITS 64
    ; use jmp / call trick to get string address in RCX
    jmp hello
back:
    ; call write(1, "Hello, World!\n", 14);
    ; rax <- 1 (__NR_write)
    ; rdi <- 1 (stdout fileno)
    ; rsi <- "Hello, World!\n"
    ; rdx <- 14 (string length)
    mov rax, 1
    mov rdi, 1
    pop rsi
    mov rdx, 14
    syscall

    ; call exit_group(0)
    ; rax <- 231 (__NR_exit_group)
    ; rdi <- 0 (exit status)
    mov rax, 231
    xor rdi, rdi
    syscall

hello:
    call back
    db "Hello, World!", 10, 0

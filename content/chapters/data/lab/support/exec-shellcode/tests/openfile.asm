BITS 64
    ; use jmp / call trick to get filename address in RCX
    jmp filename
back:
    ; call open("uberfile", O_RDWR | O_TRUNC | O_CREAT, 0644)
    ; rax <- 2 (__NR_open)
    ; rdi <- "uberfile"
    ; rsi <- 578 (O_RDWR | O_TRUNC | O_CREAT - 01102)
    ; rdx <- 420 (0644)
    mov rax, 2
    pop rdi
    mov rsi, 578
    mov rdx, 420
    syscall

    ; call exit_group(0)
    ; rax <- 231 (__NR_exit_group)
    ; rdi <- 0 (exit status)
    mov rax, 231
    xor rdi, rdi
    syscall

filename:
    call back
    db "uberfile", 0

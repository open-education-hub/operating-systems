; SPDX-License-Identifier: BSD-3-Clause

extern printf
extern pthread_create
extern pthread_join

global main

NUM_ITER equ 10000000

section .rodata
	fmt_str db "var = %d", 10, 0

section .bss
	var resd 1

section .text
increment_var:
	push rbp
	mov rbp, rsp

	mov rcx, NUM_ITER
loop_increment:
	lock inc dword [var]
	loop loop_increment

	leave
	ret

decrement_var:
	push rbp
	mov rbp, rsp

	mov rcx, NUM_ITER
loop_decrement:
	; TODO: Use `lock` to perform the following instruction atomically.
	lock dec dword [var]
	loop loop_decrement

	leave
	ret

main:
	push rbp
	mov rbp, rsp

	; pthread_t tids[2];
	sub rsp, 16

	; pthread_create(&tids[0], NULL, increment_var, NULL)
	mov rdi, rsp
	xor rsi, rsi
	mov rdx, increment_var
	xor rcx, rcx
	call pthread_create

	; pthread_create(&tids[1], NULL, decrement_var, NULL)
	lea rdi, [rsp + 8]
	xor rsi, rsi
	mov rdx, decrement_var
	xor rcx, rcx
	call pthread_create

	; pthread_join(tids[0], NULL)
	mov rdi, [rsp]
	xor rsi, rsi
	call pthread_join

	; pthread_join(tids[1], NULL)
	mov rdi, [rsp + 8]
	xor rsi, rsi
	call pthread_join

	; printf("var = %d\n", var)
	mov rdi, fmt_str
	mov esi, [var]
	call printf

	leave
	ret

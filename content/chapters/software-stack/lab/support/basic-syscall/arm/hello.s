/* SPDX-License-Identifier: BSD-3-Clause */

.section .bss

    .lcomm buffer, 128

    /*
     * We need to add some padding due to a QEMU bug, present
     * on the 4.2.1 version, that produces a SEGFAULT;
     * the program works perfectly fine otherwise
     */
    .p2align 12

.equ len, 128

.section .rodata

hello:
    .ascii "Hello, world!\n\0"

bye:
    .ascii "Bye, world!\n\0"

.section .text

.global main



main:
    /* syscall calling in arm found at */
    /* https://arm64.syscall.sh/ */

    /* needed instructions: */

    /* mov <register>, #<value> , moves an 8 bit value*/
    /* ldr <register>, =<value>,loads a value, usually an address */
    /* svc #<value>, syscall (use value 0 for syscall) */
    /* ret , return*/


    /* Call write(1, "Hello, world!\n", 14). */
    /* x8 <- __NR_write (index of write syscall: 64) */
    /* x0 <- first syscall argument (fd: 1) */
    /* x1 <- second syscall argument (buffer: hello) */
    /* x2 <- third syscall argument (length: 14) */


    /* Call exit(0). */
    /* x8 <- __NR_exit (index of exit syscall: 93) */
    /* x0 <- first syscall argument (error_code: 0) */


    ret

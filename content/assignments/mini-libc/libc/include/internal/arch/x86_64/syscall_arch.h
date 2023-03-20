/* SPDX-License-Identifier: BSD-3-Clause */

/*
 * From Musl Libc: https://musl.libc.org/
 *
 * https://git.musl-libc.org/cgit/musl/tree/arch/x86_64/syscall_arch.h
 */

#ifndef __SYSCALL_ARCH_X86_64__
#define __SYSCALL_ARCH_X86_64__		1

#ifdef __cplusplus
extern "C" {
#endif

static inline long __syscall(long n, long a1, long a2, long a3, long a4, long a5, long a6)
{
	unsigned long ret;

	register long r10 __asm__("r10") = a4;
	register long r8 __asm__("r8") = a5;
	register long r9 __asm__("r9") = a6;

	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3), "r"(r10), "r"(r8), "r"(r9) : "rcx", "r11", "memory");

	return ret;
}

#ifdef __cplusplus
}
#endif

#endif

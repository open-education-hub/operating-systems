/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef __STDARG_H__
#define __STDARG_H__	1

#ifdef __cplusplus
extern "C" {
#endif

#include <internal/types.h>

#define va_start(v, l)	__builtin_va_start(v, l)
#define va_end(v)	__builtin_va_end(v)
#define va_arg(v, l)	__builtin_va_arg(v, l)
#define va_copy(d, s)	__builtin_va_copy(d, s)

typedef __builtin_va_list va_list;

#ifdef __cplusplus
}
#endif

#endif

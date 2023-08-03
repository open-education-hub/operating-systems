/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef __STDLIB_H__
#define __STDLIB_H__	1

#ifdef __cplusplus
extern "C" {
#endif

#include <internal/types.h>
#include <internal/essentials.h>

#define EXIT_SUCCESS	0
#define EXIT_FAILURE	1

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);
long exit(long exit_code);

#ifdef __cplusplus
}
#endif

#endif

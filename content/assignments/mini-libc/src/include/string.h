/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef	__STRING_H__
#define	__STRING_H__	1

#ifdef __cplusplus
extern "C" {
#endif

#include <internal/types.h>

char *strcpy(char *destination, const char *source);
char *strncpy(char *destination, const char *source, size_t len);

char *strcat(char *destination, const char *source);
char *strncat(char *destination, const char *source, size_t len);

size_t strlen(const char *str);

int strcmp(const char *str1, const char *str2);
int strncmp(const char *str1, const char *str2, size_t len);

char *strchr(const char *str, int c);
char *strrchr(const char *str, int c);

char *strstr(const char *str1, const char *str2);
char *strrstr(const char *str1, const char *str2);

void *memcpy(void *destination, const void *source, size_t num);
void *memset(void *source, int value, size_t num);
void *memmove(void *destination, const void *source, size_t num);
int memcmp(const void *ptr1, const void *ptr2, size_t num);

#ifdef __cplusplus
}
#endif

#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct String_Internal
{
    char* ptr;
    size_t len;
    int capacity;
};

typedef union String
{
    struct String_Internal long_str;
    char small_str[24];
}String;

void initString(String* str, char* ptr)
{
    size_t len = strlen(ptr);
    if (len < 16)
    {
        strncpy(str->small_str, ptr, len);
        str->long_str.capacity = -1;
    }
    else
    {
        str->long_str.ptr = malloc(len*2);
        strncpy(str->long_str.ptr, ptr, len);
        str->long_str.len = len;
        str->long_str.capacity = len*2;
    }
}

void appendStr(String str1, String str2);
void appendCharArray(String str1, char* str2);
char indexOf(size_t idx);
/* ... */

char* getString(String* str)
{
    if (str->long_str.capacity == -1)
        return str->small_str;
    else
        return str->long_str.ptr;
}

void main()
{
    /*printf("sizeof(String_Internal: %lu)\n", sizeof(struct String_Internal));*/
    String s;
    initString(&s, "hello");
    printf("%s\n", getString(&s));

    String s2;
    initString(&s, "hello baby, yuhuu");
    printf("%s\n", getString(&s));
}

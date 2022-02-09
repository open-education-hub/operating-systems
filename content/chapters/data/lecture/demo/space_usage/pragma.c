#include <stdio.h>

/*#pragma pack(1)*/
struct S
{
    char a;
    int b;
};

void main()
{
    printf("sizeof(S) = %lu\n", sizeof(struct S));

    struct S s;

    printf("%x\n", &s.a);
    printf("%x\n", &s.b);

}

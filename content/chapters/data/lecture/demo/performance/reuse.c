#include <stdlib.h>

void* allocateArray(size_t numElems, size_t elemSize)
{
    return malloc(numElems * elemSize);
}

void deallocateArray(void* array)
{
    free(array);
}

void main()
{
    int* intArray = allocateArray(10, sizeof(int));
    /*printf("%x\n", intArray);*/

    /* do some stuff with intArray */

    deallocateArray(intArray);

    /* do some other stuff */

    // we could just use intArray instead
    char* charArray = allocateArray(20, sizeof(char));
    /*printf("%x\n", charArray);*/

    /* do some stuff with charArray */

    deallocateArray(charArray);
}

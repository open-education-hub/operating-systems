#include <time.h>
#include <stdlib.h>

#include "generate_random_array.h"

void generateRandomArray(size_t length, int array[])
{
	srand(time(0));

	for (int i = 0; i < length; i++)
	{
		array[i] = rand() % MAX_ELEMENT;
	}
}

// SPDX-License-Identifier: BSD-3-Clause

#include <time.h>
#include <stdlib.h>
#include <stdint.h>

#include "include/generate_random_array.h"

void generate_random_array(size_t length, int array[])
{
	uint32_t seed = time(0);

	for (size_t i = 0; i < length; i++)
		array[i] = rand_r(&seed) % MAX_ELEMENT;
}

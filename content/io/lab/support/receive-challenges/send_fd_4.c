// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>

#include "utils/utils.h"

static const char FLAG[] = "SO{in_the_pipe_five_by_five}\n";

int main(void)
{
	write(4, FLAG, sizeof(FLAG));
	return 0;
}

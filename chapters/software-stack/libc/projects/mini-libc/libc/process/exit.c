// SPDX-License-Identifier: BSD-3-Clause

#include <internal/syscall.h>
#include <stdlib.h>

long exit(long exit_code)
{
	return syscall(__NR_exit, exit_code);
}

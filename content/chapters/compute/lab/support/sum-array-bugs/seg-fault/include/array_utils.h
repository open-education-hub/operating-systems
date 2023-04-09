/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#define ARR_LEN 100000000

#define min(a, b)			\
	({				\
		__typeof__(a) _a = (a);	\
		__typeof__(b) _b = (b);	\
		_a < _b ? _a : _b;	\
	})

#endif /* ARRAY_UTILS_H */

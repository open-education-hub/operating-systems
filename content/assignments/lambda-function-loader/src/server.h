/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef SERVER_H
#define SERVER_H

/* lambda function without parameter */
typedef void (*lambda_func_t)(void);

/* lambda function with parameter */
typedef void (*lambda_param_func_t)(const char *);

struct lib {
	char *outputfile;
	char *libname;
	char *funcname;
	char *filename;

	void *handle;

	lambda_func_t run;
	lambda_param_func_t p_run;
};

#endif /* SERVER_H */

/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <openssl/sha.h>

#include "../utils/utils.h"

#define NUM_WORKERS 26
#define PASSWORD_LEN 4
#define PASSWORD_HASH "\x59\xa5\xab\xc2\xa9\x9b\x95\xbe"		\
	"\x73\xc3\x1e\xa2\x72\xab\x0f\x2f"				\
	"\x2f\xe4\x2f\xec\x30\x36\x71\x55"				\
	"\xcb\x73\xf6\xf6\xce\xf1\xf4\xe6"				\
	"\xee\x37\xf5\x86\xcb\xd0\x2c\xc7"				\
	"\x38\xa8\x7a\x5d\x6a\xdd\x3b\xa3"				\
	"\x1d\xbe\xaf\x39\xec\x77\xca\xd9"				\
	"\x10\x83\x7c\x94\xc6\x58\x37\xfb"
#define HASH_LEN 64

int check_password(char *password, int len)
{
	unsigned char hash[HASH_LEN];

	SHA512((unsigned char *)password, len, hash);

	return memcmp(hash, PASSWORD_HASH, HASH_LEN) == 0;
}

void worker(int idx, int request_pipe_fd, int result_pipe_fd)
{
	char first_char;
	int ret;
	char password[PASSWORD_LEN+1];
	int i, k;
	int found = 0;
	int v;

	/*
	 * Read the first character of the password.
	 */

	ret = read(request_pipe_fd, &first_char, sizeof(first_char));
	DIE(ret <= 0, "read");

	password[0] = first_char;

	for (i = 1; i < PASSWORD_LEN; i++)
		password[i] = 'a'-1;


	/*
	 * Generate all possible combinations.
	 */
	k = 1;

	while (k >= 1) {
		if (password[k] < 'z') {
			password[k]++;

			if (k < PASSWORD_LEN) {
				k++;
				password[k] = 'a'-1;
			}
		}

		if (k == PASSWORD_LEN) {
			/* Check one combination */
			if (check_password(password, PASSWORD_LEN)) {
				found = 1;
				break;
			}
		}

		if ((password[k] == 'z') || (k == PASSWORD_LEN)) {
			k--;
		}
	}

	if (found) {
		/*
		 * Found the password. Send the password length and the password
		 * through the pipe.
		 */
		v = PASSWORD_LEN;

		ret = write(result_pipe_fd, &v, sizeof(v));
		DIE(ret < 0, "write");

		ret = write(result_pipe_fd, password, PASSWORD_LEN);
		DIE(ret < 0, "write");
	} else {
		/*
		 * Didn't find the password. Send the value 0 through the pipe.
		 */
		v = 0;

		ret = write(result_pipe_fd, &v, sizeof(v));
		DIE(ret < 0, "write");
	}
}

void create_workers(int *request_pipefd, int *result_pipefd)
{
	int tmp_request_pipe[2];
	int tmp_result_pipe[2];
	int ret;
	int pid;
	int i;

	for (i = 0; i < NUM_WORKERS; i++) {
		/* Create the request pipe. */
		ret = pipe(tmp_request_pipe);
		DIE(ret < 0, "pipe");

		/* Create the result pipe. */
		ret = pipe(tmp_result_pipe);
		DIE(ret < 0, "pipe");

		pid = fork();
		DIE(pid < 0, "fork");

		if (pid == 0) {
			/*
			 * In child process.
			 *
			 * Close the unused pipe ends:
			 * - the write end of the request pipe, since the child will only read from this pipe.
			 * - the read end of the result pipe, since the child will only write to this pipe.
			 */
			close(tmp_request_pipe[1]);
			close(tmp_result_pipe[0]);

			/* Call the worker function. */
			worker(i, tmp_request_pipe[0], tmp_result_pipe[1]);

			exit(0);
		}

		/*
		 * In parent process.
		 *
		 * Close the unused pipe ends:
		 * - the read end of the request pipe, since the parent will only write to this pipe.
		 * - the write end of the result pipe, since the parent will only read from this pipe.
		 */
		close(tmp_request_pipe[0]);
		close(tmp_result_pipe[1]);

		request_pipefd[i] = tmp_request_pipe[1];
		result_pipefd[i] = tmp_result_pipe[0];
	}
}

int main()
{
	int i;
	int request_pipefd[NUM_WORKERS];
	int result_pipefd[NUM_WORKERS];
	int len;
	int ret;
	char char_list[] = "abcdefghijklmnopqrstuvwxyz";
	char password[PASSWORD_LEN+1];

	create_workers(request_pipefd, result_pipefd);

	/*
	 * Send the first character of the password to each worker.
	 */
	for (i = 0; i < NUM_WORKERS; i++) {
		ret = write(request_pipefd[i], &char_list[i], sizeof(char));
		DIE(ret < 0, "write");
	}

	for (i = 0; i < NUM_WORKERS; i++) {
		/*
		 * Read the result for each worker.
		 */
		ret = read(result_pipefd[i], &len, sizeof(len));
		DIE(ret < 0, "read");

		if (len) {
			ret = read(result_pipefd[i], password, len);
			DIE(ret < 0, "read");

			password[len] = 0;

			printf("worker %d found %s\n", i, password);
		}
	}

	for (i = 0; i < NUM_WORKERS; i++) {
		ret = wait(NULL);
		DIE(ret < 0, "wait");
	}

	return 0;
}

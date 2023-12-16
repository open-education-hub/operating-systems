// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/ipc.h"

int main(int argc, char *argv[])
{
	int fd = -1;
	int ret = -1;

	/* Buffer for the command to be sent to the server. */
	char buf[BUFSIZE];

	memset(buf, 0, BUFSIZE);

	/* Format command based on program arguments. */
	switch (argc) {
	case 2:
		snprintf(buf, BUFSIZE, "%s", argv[1]);
		break;
	case 3:
		snprintf(buf, BUFSIZE, "%s %s", argv[1], argv[2]);
		break;
	case 4:
		snprintf(buf, BUFSIZE, "%s %s %s", argv[1], argv[2], argv[3]);
		break;
	default:
		fprintf(stderr, "Illegal client format\n");
		exit(-1);
	}

	/* Create the socket to be used for communication with the server. */
	fd = create_socket();
	if (fd == -1) {
		perror("unix socket");
		exit(-1);
	}

	/* Connect to the socket used to communicate with the server. */
	ret = connect_socket(fd);

	if (ret == -1) {
		perror("connect unix socket");
		exit(-1);
	}

	/* Send the command to the server. */
	send_socket(fd, buf, strlen(buf));

	/* Wait for the response from the server. */
	memset(buf, 0, BUFSIZE);
	recv_socket(fd, buf, BUFSIZE);
	buf[BUFSIZE - 1] = 0;

	/* Print the result. */
	printf("Output file: %s\n", buf);

	/* Close connection with the server. */
	close_socket(fd);

	return 0;
}

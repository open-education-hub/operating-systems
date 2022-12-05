/*
 * Use ioctl to get MAC address of network interface.
 *
 * Some inspiration from Stack Overflow
 * http://stackoverflow.com/questions/1779715/how-to-get-mac-address-of-your-machine-using-a-c-program
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netdb.h>
#include <linux/if.h>

#include "utils/utils.h"

#define IFNAME			"enp0s31f6"

int main(void)
{
	int s;
	struct ifreq ifr;
	int rc;
	size_t i;

	// Create socket
	s = socket(PF_INET, SOCK_DGRAM, 0);
	DIE(s < 0, "socket");

	// Call ioctl to populate ifr struct
	snprintf(ifr.ifr_name, strlen(IFNAME)+1, "%s", IFNAME);
	rc = ioctl(s, SIOCGIFHWADDR, &ifr);
	DIE(rc < 0, "ioctl");

	// Print result
	printf("Hardware address for interface %s is ", IFNAME);
	for (i = 0; i < IFHWADDRLEN-1; i++)
		printf("%02x:", ((unsigned char *) ifr.ifr_hwaddr.sa_data)[i]);
	printf("%02x", ((unsigned char *) ifr.ifr_hwaddr.sa_data)[IFHWADDRLEN-1]);
	printf("\n");

	close(s);
	return 0;
}

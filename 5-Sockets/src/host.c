//
//  Exercise 5 - Simulating a Remote Temperature Sensor using UNIX-Domain Sockets
//
//  host.c
//
//  Samuel von Baussnern
//  S09-914-623
//  samuel.vonbaussnern@uzh.ch
//  Systems Software, FS14, UZH Zurich
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stddef.h>

#include "defaults.h"
#include "utils.h"

int main(int argc, const char* argv[]) {
	if (argc != 3) {
		const char err_msg[] = "Wrong number of arguments";
		const char usage_msg[] = "Usage: host <String: socket address> <String: auth token>";
		printf("%s\n%s\n", err_msg, usage_msg);
		exit(EXIT_FAILURE);
	}

	struct sockaddr_un addr;
	socklen_t addr_len;
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, argv[1]);
	addr_len = sizeof(addr);

	int fd_c;
	if ((fd_c = connect_retry(AF_UNIX, SOCK_STREAM, 0, (struct sockaddr*) &addr,
			addr_len)) < 0) {
		perror("Couldn't establish a connection.");
		exit(EXIT_FAILURE);
	}

	write(fd_c, argv[2], strlen(argv[2])); // the termination character doesn't have to be transmitted

	char buf[255];
	ssize_t nr = read(fd_c, buf, 255);
	buf[nr] = '\0';

	printf("Received: %s\n", buf);

	close(fd_c);

	const char end_msg[] = "Press RETURN to exit!";
	printf("%s\n", end_msg);
	getchar();

	exit(EXIT_SUCCESS);
}

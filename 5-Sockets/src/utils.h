//
//  Exercise 5 - Simulating a Remote Temperature Sensor using UNIX-Domain Sockets
//
//  utils.h
//
//  Samuel von Baussnern
//  S09-914-623
//  samuel.vonbaussnern@uzh.ch
//  Systems Software, FS14, UZH Zurich
//
#include <errno.h>
#include <sys/socket.h>

#define MAXSLEEP 128

int initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen);
int connect_retry(int domain, int type, int protocol,
		const struct sockaddr *addr, socklen_t alen);
void signalHandler(int signum);

int initserver(int type, const struct sockaddr *addr, socklen_t alen,
		int qlen) {
	int fd;
	int err = 0;

	if ((fd = socket(addr->sa_family, type, 0)) < 0) {
		return (-1);
	}

	if (bind(fd, addr, alen) < 0) {
		goto ERROUT_INITSERVER;
	}

	if (type == SOCK_STREAM || type == SOCK_SEQPACKET) {
		if (listen(fd, qlen) < 0) {
			goto ERROUT_INITSERVER;
		}
	}

	return (fd);

	ERROUT_INITSERVER: err = errno;
	close(fd);
	errno = err;
	return (-1);
}

/**
 * Using exponential backoff to establish a connection
 * (used only in connection-oriented network service.)
 * @param  domain   Nature of the communication, including the address format.
 * @param  type     Type of the socket. Here `SOCK_STREAM` or `SOCK_SEQPACKET`.
 * @param  protocol Used protocol for the given domain and type. Default: 0.
 * @param  addr     Address of the socket
 * @param  alen     Size of socket address
 * @return          On success returns a connected socket descriptor, on failure -1.
 */
int connect_retry(int domain, int type, int protocol,
		const struct sockaddr *addr, socklen_t alen) {
	int numsec, fd;

	//
	// Try to connect with exponential backoff.
	//
	for (numsec = 1; numsec <= MAXSLEEP; numsec <<= 1) {
		if ((fd = socket(domain, type, protocol)) < 0) {
			return (-1);
		}

		if (connect(fd, addr, alen) == 0) {
			return (fd); // Connection accepted.
		}

		close(fd);

		// Delay before trying again.
		if (numsec <= MAXSLEEP / 2) {
			sleep(numsec);
		}
	}

	return (-1);
}

void signalHandler(int signum) {
	printf("Interrupt signal; Program terminated.\n");

	const char end_msg[] = "Press RETURN to exit!";
	printf("%s\n", end_msg);

	getchar();

	exit(signum);
}

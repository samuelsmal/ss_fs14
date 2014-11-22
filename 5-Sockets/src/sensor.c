//
//  Exercise 5 - Simulating a Remote Temperature Sensor using UNIX-Domain Sockets
//
//  sensor.c
//
//  Systems Software, FS14, UZH Zurich
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stddef.h>
#include <errno.h>
#include <signal.h>

#include "defaults.h"
#include "utils.h"

int initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen);
void signalHandler(int signum) __attribute__ ((noreturn));

static const char *SOCKET_ADDRESS;
static int SERVER_SOCKET;

int main(int argc, const char* argv[]) {
	if (argc != 2) {
		const char err_msg[] = "Wrong number of arguments";
		const char usage_msg[] = "Usage: sensor <String: socket address>";
		printf("%s\n%s\n", err_msg, usage_msg);
		exit(EXIT_FAILURE);
	}

  SOCKET_ADDRESS = argv[1];

	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = signalHandler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);

	struct sockaddr_un addr_client;
	socklen_t addr_client_len;

	struct sockaddr_un addr_server;
	addr_server.sun_family = AF_UNIX;
	strcpy(addr_server.sun_path, SOCKET_ADDRESS);
	socklen_t
	addr_server_len = offsetof( struct sockaddr_un, sun_path ) + strlen( addr_server.sun_path );

  unlink(argv[1]);

	if ((SERVER_SOCKET = initserver(SOCK_STREAM,
			(struct sockaddr*) &addr_server, addr_server_len, 10)) < 0) {
		exit(EXIT_FAILURE);
	}

	while (1) {
		if (listen(SERVER_SOCKET, 1) < 0) {
			perror("Error in listen()");
			exit(EXIT_FAILURE);
		}

		// ***   accept an incoming connection   ***

		addr_client_len = sizeof(struct sockaddr_un);
		int client_socket = accept(SERVER_SOCKET,
				(struct sockaddr*) &addr_client, &addr_client_len);

		if (client_socket < 0) {
			perror("Error in accept()");
			exit(EXIT_FAILURE);
		} else {
			printf("Connection established! (%d) Waiting for request...\n",
					client_socket);
		}

		int temperature = rand() % 99 + 10;

		pid_t pid = fork();
		if (pid == -1) {
			printf("fork error\n");
			exit(1);
		} else if (pid == 0) {
			// ***	child process	***

			char buf[80];
			ssize_t nr = read(client_socket, buf, 80);

			buf[nr] = '\0';
			printf("Received: %s (id = %d)\n", buf, client_socket);

			char output[80];
			sprintf(output, "%d", temperature);

			if (strncmp(buf, AUTH_TOKEN, 3) == 0) {
				write(client_socket, output, 2);
				printf("Sent: %s (id = %d)\n", output, client_socket);
			} else {
				write(client_socket, "ERR", 3);
				printf("Sent: ERR (id = %d)\n", client_socket);
			}

			// ***   close sockets   ***

			close(client_socket);
			exit(EXIT_SUCCESS);
		} else {
			// *** main(parent) process	***

			signal(SIGCHLD, SIG_IGN);
		}
	}
  exit(EXIT_SUCCESS);
}

void signalHandler(int signum) {
  printf("\nInterrupt signal received...\nProgram terminating...\n");
  close(SERVER_SOCKET);
  unlink(SOCKET_ADDRESS);
  printf("%s\n", "Done.");
  exit(signum);
}

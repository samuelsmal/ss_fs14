//
//  host.c
//
//  Samuel von Baussnern
//  S09-914-623
//  samuel.vonbaussnern@uzh.ch
//  Systems Software, FS14, UZH Zurich
//
//  Exercise 5 - Simulating a Remote Temperature Sensor using UNIX-Domain Sockets
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stddef.h>

#define MAXSLEEP 128

int connect_retry(int domain, int type, int protocol, const struct sockaddr *addr, socklen_t alen);

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    const char err_msg[] = "Wrong number of arguments";
    const char usage_msg[] = "Usage: host <String: auth token>";
    printf("%s\n%s\n", err_msg, usage_msg);
    exit(EXIT_FAILURE);
  }

  struct sockaddr_un addr;
  socklen_t addr_len;
  addr.sun_family = AF_UNIX;
  strcpy( addr.sun_path, "./sample.socket" );
  addr_len = sizeof( addr );

  int fd_c = connect_retry(AF_UNIX, SOCK_STREAM, 0, ( struct sockaddr* )&addr, addr_len);
  if( fd_c < 0 ) {
    printf("%s\n", "Couldn't establish a connection.");
    exit(EXIT_FAILURE);
  }

  write( fd_c, argv[1], strlen(argv[1]) ); // the termination character doesn't have to be transmitted

  char buf[255];
  size_t nr = read ( fd_c, buf, 255);
  buf[nr] = '\0';

  printf("%s\n", buf);

  close( fd_c );

  exit(EXIT_SUCCESS);
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
int connect_retry(int domain, int type, int protocol, const struct sockaddr *addr, socklen_t alen) {
  int numsec, fd;

  //
  // Try to connect with exponential backoff.
  //
  for (numsec = 1; numsec <= MAXSLEEP; numsec <<= 1) {
    if ((fd = socket(domain, type, protocol)) < 0) {
      return(-1);
    }

    if (connect(fd, addr, alen) == 0) {
      return(fd); // Connection accepted.
    }

    close(fd);

    // Delay before trying again.
    if (numsec <= MAXSLEEP / 2) {
      sleep(numsec);
    }
  }

  return(-1);
}

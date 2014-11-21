//
//  Exercise 5 - Simulating a Remote Temperature Sensor using UNIX-Domain Sockets
//
//  sensor.c
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
#include <errno.h>

#include "defaults.h"
#include "utils.h"

int initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen);

int main() {
  // TODO shutdown gracefully
  // TODO enable mulitiple hosts

  struct sockaddr_un addr_client;
  socklen_t addr_client_len;

  struct sockaddr_un addr_server;
  addr_server.sun_family = AF_UNIX;
  strcpy( addr_server.sun_path, SOCKET_NAME );
  socklen_t addr_server_len = offsetof( struct sockaddr_un, sun_path ) + strlen( addr_server.sun_path );

  int server_socket;
  if ( ( server_socket = initserver( SOCK_STREAM, ( struct sockaddr* )&addr_server, addr_server_len, 10) ) < 0) {
    exit(EXIT_FAILURE);
  }

  if( listen( server_socket, 1 ) < 0 ) {
    perror("Error in listen()");
    exit(EXIT_FAILURE);
  }

  // ***   accept an incoming connection   ***

  addr_client_len = sizeof( struct sockaddr_un );
  int client_socket = accept( server_socket, ( struct sockaddr* )&addr_client, &addr_client_len );

  if( client_socket < 0 ) {
    perror("Error in accept()");
    exit(EXIT_FAILURE);
  }

  char buf[ 80 ];
  ssize_t nr = read( client_socket, buf, 80 );

  buf[ nr ] = '\0';
  printf("%s\n", buf);

  const char correct_auth_token[] = "TMP";

  if (strncmp(buf, correct_auth_token, 3) == 0) {
    write( client_socket, "10", 2 );
  } else {
    write( client_socket, "ERR", 3 );
  }

  // ***   close sockets   ***

  close( client_socket );
  close( server_socket );

  unlink( SOCKET_NAME );

  exit(EXIT_SUCCESS);
}

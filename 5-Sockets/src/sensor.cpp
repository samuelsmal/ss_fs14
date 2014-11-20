//
//  pat_matching
//
//  main.cpp
//
//  Samuel von Baussnern
//  S09-914-623
//  samuel.vonbaussnern@uzh.ch
//  Systems Software, FS14, UZH Zurich
//
//  Exercise 5 - Simulating a Remote Temperature Sensor using UNIX-Domain Sockets
//

#include <iostream>

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stddef.h>

int create_server_socket();

int main() {
  int server_socket = create_server_socket();

  struct sockaddr_un addr_client;
  socklen_t addr_client_len;

  if( listen( server_socket, 1 ) < 0 )
  {
    std::cerr << "Error in listen()" << std::endl;
    return -1;
  }

  // ***   accept an incoming connection   ***

  addr_client_len = sizeof( struct sockaddr_un );
  int client_socket = accept( server_socket, ( struct sockaddr* )&addr_client, &addr_client_len );

  if( client_socket < 0 )
  {
    std::cerr << "Error in accept()" << std::endl;
    return -1;
  }

  char buf[ 80 ];
  size_t nr = read( client_socket, buf, 80 );

  buf[ nr ] = '\0';
  std::cout << buf << std::endl;


  // ***   close sockets   ***

  close( client_socket );
  close( server_socket );

  unlink( "./sample.socket" );

  return 0;
}

int create_server_socket() {
  int server_socket = socket( AF_UNIX, SOCK_STREAM, 0 );
  if( server_socket < 0 )
  {
    std::cerr << "Error in socket()" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  struct sockaddr_un addr_server;
  addr_server.sun_family = AF_UNIX;
  strcpy( addr_server.sun_path, "./sample.socket" );
  socklen_t addr_server_len = offsetof( struct sockaddr_un, sun_path ) + strlen( addr_server.sun_path );

  if( bind( server_socket, ( struct sockaddr* )&addr_server, addr_server_len ) < 0 )
  {
    std::cerr << "Error in bind()" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  return server_socket;
}

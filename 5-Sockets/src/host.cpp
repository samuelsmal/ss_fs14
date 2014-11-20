#include <iostream>

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stddef.h>


int main() {

  struct sockaddr_un addr_s;
  socklen_t addr_s_len;

  int fd_c = socket( AF_UNIX, SOCK_STREAM, 0 );
  if( fd_c < 0 )
  {
    std::cerr << "Error in socket()" << std::endl;
    return -1;
  }

  addr_s.sun_family = AF_UNIX;
  strcpy( addr_s.sun_path, "./sample.socket" );
  addr_s_len = sizeof( addr_s );
  if( connect( fd_c, ( struct sockaddr* )&addr_s, addr_s_len )  <  0 )
  {
    std::cerr << "Error in connect()" << std::endl;
    return -1;
  }

  char buf[ 4 ] = "MSG"; // the last bit is the termination character \0
  write( fd_c, buf, 3 ); // the termination character doesn't have to be transmitted

  close( fd_c );

  return 0;
}

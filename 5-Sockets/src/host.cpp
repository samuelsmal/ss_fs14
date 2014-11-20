#include <iostream>

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stddef.h>


int main()
{
  int fd_c;

  struct sockaddr_un addr_s;
  socklen_t addr_s_len;


  // ***   create socket   ***

  fd_c = socket( AF_UNIX, SOCK_STREAM, 0 );
  if( fd_c < 0 )
  {
    std::cerr << "Error in socket()" << std::endl;
    return -1;
  }


  // ***   establish connection   ***

  addr_s.sun_family = AF_UNIX;
  strcpy( addr_s.sun_path, "./sample.socket" );
  addr_s_len = sizeof( addr_s );
  if( connect( fd_c, ( struct sockaddr* )&addr_s, addr_s_len )  <  0 )
  {
    std::cerr << "Error in connect()" << std::endl;
    return -1;
  }


  // ***   write message   ***

  char buf[ 3 ];

  buf[ 0 ] = 'M';
  buf[ 1 ] = 'S';
  buf[ 2 ] = 'G';
  write( fd_c, buf, 3 );


  // ***   close socket   ***

  close( fd_c );

  return 0;
}

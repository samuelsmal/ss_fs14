#include <iostream>

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stddef.h>


int main(int argc, const char* argv[]) {
  if (argc != 2) {
    std::cerr << "Wrong number of arguments"
      << "\n\t Usage: host <String: auth token>"
      << std::endl;
  }


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

  write( fd_c, argv[1], strlen(argv[1]) ); // the termination character doesn't have to be transmitted

  char buf[255];
  size_t nr = read ( fd_c, buf, 255);
  buf[nr] = '\0';

  std::cout << buf << std::endl;

  close( fd_c );

  return 0;
}

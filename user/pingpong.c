#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{

  int p2c[2], c2p[2];

  pipe(p2c);
  pipe(c2p);
  
  char buffer[5];

  if (fork() == 0) {
    read(p2c[0], buffer, 5);
    printf("%d: received %s\n",  getpid(), buffer);
    write(c2p[1], "pong", 5);
    exit(0);
  } else {
    write(p2c[1], "ping", 5);
    read(c2p[0], buffer, 5);
    printf("%d: received %s\n", getpid(), buffer);
    exit(0);
  }
}

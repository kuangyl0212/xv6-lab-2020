#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  char buff[512]; 
  for (int i = 0; i < argc; i ++) {
    printf("%s\n", argv[i]);
  }
  read(0, buff, 512);
  printf("%s\n", buff);
  exit(0);
}

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void
find(char *path, char *name)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    fprintf(2, "find: you should find in a directory\n");
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
    //   printf("de.name: %s\n", de.name);
    //   printf("buf: %s\n", buf);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        // printf("ls: cannot stat %s\n", buf);
        continue;
      }
      if (st.type == T_FILE && strcmp(de.name, name) == 0) {
          printf("%s\n", buf);
      }
      if (st.type == T_DIR && strcmp(de.name, ".") != 0 && strcmp(de.name, "..") != 0) {
          find(buf, name);
      }
    //   find(buf, name);
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{

  if(argc < 2){
    fprintf(2, "find: arguments not enough\n");
    exit(1);
  }
  find(argv[1], argv[2]);
  exit(0);
}

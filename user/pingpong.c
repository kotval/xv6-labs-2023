#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
  int fd1[2];
  int fd2[2];
  pipe(fd1);
  pipe(fd2);
  // in child process
  if(fork() == 0){
    char resc_byte[1] = {0};
    close(fd1[1]);
    read(fd1[0],resc_byte,1);
    close(fd1[0]);
    if (resc_byte[0] == '9'){
      printf("%d: received ping\n",getpid());
      write(fd2[1],resc_byte,1);
      exit(0);
    }
    exit(1);
  }
  // in parent
  else{
    char the_byte[1] = {'9'};
    close(fd1[0]);
    write(fd1[1],the_byte,1);
    // close writing end of pipe
    close(fd2[1]);
    char resc_byte_from_child[1] = {0};
    read(fd2[0],resc_byte_from_child,1);
    if (resc_byte_from_child[0] == '9'){
      printf("%d: received pong\n",getpid());
    }
  }
  exit(0);
}

#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(!(argc == 2)){
    fprintf(2, "Sleep requires a number of ticks\n");
    exit(1);
  }
  else{
    sleep(atoi(argv[1]));
    exit(0);
  }
}

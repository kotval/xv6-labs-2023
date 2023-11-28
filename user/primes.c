#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
  // parent process feeds the numbers from 2 to 35 to the pipeline
  // for each prime it creates one process that reads from left neighbor
  // over a pipe and writes to right neighbor over another pipe.
  //
  int parent;
  int child[2];
  pipe(child);
  for(int i = 2; i <= 35; i++){
    write(child[1],&i,sizeof(int));
  }
  close(child[1]);
  parent = child[0];
  int input;
  int prime;
  while(read(parent,&prime,sizeof(int))){
    printf("prime %d\n", prime);
    pipe(child);
    if(fork() == 0){
      //is input coprime with parent 
      while(read(parent,&input,sizeof(int))){
        if(input % prime != 0){
          write(child[1],&input,sizeof(int));
        }
        //else drop 
      }
      close(child[1]);
      close(parent);
      exit(0);
    }
    close(child[1]);
    close(parent);
    parent = child[0];
  }
  exit(0);
}

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int printErr(){
  printf("Error %d: %s\n", errno, strerror(errno));
  return -1;
}

int randNum(){
  srand(getpid());
  int randNum = rand()%5+1; // print random number in the range [1,5]
  return randNum;
}


int main(){

  printf("%d about to create 2 child processes.\n", getpid());

  pid_t p1 = fork();

  if(p1<0){
    perror("fork fail");
    exit(1);
  } else if (p1 == 0){ // child
      int randOne = randNum();
      printf("%d      %d secs\n", getpid(), randOne);
      sleep(randOne);
      printf("%d finished after %d seconds.\n", getpid(), randOne);
      exit(randOne);
  }

  pid_t p2 = fork();

  if(p2<0){
    perror("fork fail");
    exit(1);
  } else if (p2 == 0){ // child
      int randTwo = randNum();
      printf("%d      %d secs\n", getpid(), randTwo);
      sleep(randTwo);
      printf("%d finished after %d seconds.\n", getpid(), randTwo);
      exit(randTwo);
  }

  /*
  wait(int* status)
  Pass in an address to an int status which is used to store information about how the process exited.
  */

  int status;
  pid_t done = wait(&status);
  if(WIFEXITED(status) && done!=-1){
    printf("Main Process %d is done. Child %d slept for %d sec\n", getpid(), done, WEXITSTATUS(status));
  }
  if(done == 0) printErr();
}

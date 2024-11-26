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

  int randOne = randNum();
  if(p1<0){
    perror("fork fail");
    exit(1);
  } else if (p1 == 0){ // child
      printf("%d      %d secs\n", getpid(), randOne);
      sleep(randOne);
      printf("%d finished after %d seconds.\n", getpid(), randOne);
      exit(randOne);
  }

  pid_t p2 = fork();

  int randTwo = randNum();
  if(p2<0){
    perror("fork fail");
    exit(1);
  } else if (p2 == 0){ // child
      printf("%d      %d secs\n", getpid(), randTwo);
      sleep(randTwo);
      printf("%d finished after %d seconds.\n", getpid(), randTwo);
      exit(randTwo);
  }

  if(WIFEXITED); // works if null but not with the WIFEXITED... what's up with that
  printf("Main Process %d is done. Child %d slept for %d sec\n", getpid(), p1, randOne);
}

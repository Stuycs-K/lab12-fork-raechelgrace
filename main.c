#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int printErr(){
  perror("Error %d: %s\n", errno, strerror(errno));
  return -1;
}


// /dev/random for random
//
// You can read bytes from /dev/random to return random bytes from the 'entropy pool'.
// When the entropy pool is empty (you read too many values), reads from /dev/random will block until additional environmental noise is gathered.
// /dev/random is be suitable for uses that need very high quality randomness such as one-time pad or key generation.
//
//

printf("%d about to create 2 child processes.\n", getpid());

pid_t p;
p = fork();

// fork twice? p1 and p2?

if(p<0){
  perror("fork fail");//output to stderr instead of stdout
  exit(1);
} else if ( p == 0){ // child
    printf("%d\n", getpid());
    int rand = 1; // print random number in the range [1,5]
    sleep(rand);
    printf("%d finished after %d seconds.\n", getpid(), rand);
}else{ // parent
  wait(WIFSIGNALED); // is this the right wait signal?
  printf("Main Process %d is done. Child %d slept for %d sec", getpid(), p, rand);
}

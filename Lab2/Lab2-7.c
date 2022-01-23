// Name: Justin Li
// Date: 1/14/21
// Title: Lab2 Part7 - Programming in C and use of Systems Calls
// Description: This program has the child process runs the ls command, and the parent process waits until the child process terminates before it exits

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
 
/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    pid_t pid;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\n Before forking.\n");
    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }    
    else if(pid == 0){
        execlp("/bin/ls", "ls", NULL);
    }
    else{
	// Child process
        wait(NULL);
        printf("Child Complete");
        exit(0);
  }
   return 0;
}

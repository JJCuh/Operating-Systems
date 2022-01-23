// Name: Justin Li
// Date: 1/14/21
// Title: Lab2 Step5
// Description: This program creates 7 different processes using fork()

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
    else if (pid){
	fork();
        printf("This is process pid=%d, the parent process is ppid=%d\n", getpid(), getppid());
	usleep(n);
    }
    else {
	pid = fork();
	if (pid){
		fork();
		printf("This is process pid=%d, the parent process is ppid=%d\n", getpid(), getppid());
		usleep(n);
	}
	else {
		pid = fork();
		if (pid) {
			fork();
			printf("This is process pid=%d, the parent process is ppid=%d\n", getpid(), getppid());
			usleep(n);
		}
		else {
			printf("This is process pid=%d, the parent process is ppid=%d\n", getpid(), getppid());
			usleep(n);
		}
    	usleep(n);
	}
    usleep(n);
    }
    return 0;
}

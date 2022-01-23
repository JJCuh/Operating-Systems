// Name: Justin Li
// Date: 1/31/21
// Title: Lab3 Part5 - Pthreads and inter-process Communication – Pipes
// Description: C program that implements the producer-consumer message communication using pipes. 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h>

// main
int main(int argc,char *argv[]){
   int  fds[2];
   char buff[60];
   int count;
   int i;
   pipe(fds);   
   if (fork()==0){
       printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
       close(fds[0]);
       for(i=0;i<argc;i++){
          strcat(buff, argv[i]); // copies string into buffer
       }
	write(fds[1], buff, strlen(buff)); // write buffer in fds
       exit(0);
   }
   else if(fork()==0){
       printf("\nReader on the downstream end of the pipe \n");
       close(fds[1]);
       read(fds[0], buff, 60); // read buffer in fds
       printf("\n");
       write(1,buff,60); // print out message
       printf("\n");
       exit(0);
    }
   else{     
      close(fds[0]);
      close(fds[1]);
      wait(0);
      wait(0);
   }
return 0;
}


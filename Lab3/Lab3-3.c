// Name: Justin Li
// Date: 1/31/21
// Title: Lab3 Part3 - Pthreads and inter-process Communication  Pipes
// Description: Modified version of Step 2 where the writer process passes the output of ls command to the upstream end of the pipe

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h> 

//main
int main(int argc, char *argv[]){
   int  fds[2];
   char buff[60];
   int count;
   int i;
   pipe(fds);   
   if (fork()==0){
       printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
       dup2(fds[1], 1);
       close(fds[0]);
       execlp("ls", "ls", 0);  
       for(i=0;i<argc;i++){
           write(fds[1],argv[i],strlen(argv[i]));
       }
       exit(0);
   }
   else if(fork()==0){
       printf("\nReader on the downstream end of the pipe \n");
       close(fds[1]);
       while((count=read(fds[0],buff,60))>0){
           for(i=0;i<count;i++){
               write(1,buff+i,1);
               write(1," ",1);
           }
           printf("\n");
       }
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


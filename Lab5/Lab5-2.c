// Name: Justin Li 
// Date: 2/11/21 
// Title: Lab5 – task2 
// Description: This program is threadSync.c - multi-threaded program with added mutex locks and critical sections

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#define NTHREADS 10

pthread_t threads[NTHREADS];
pthread_mutex_t m;

void* go(void *arg){
	// replacing with mutex_lock and mutex_unlock
	pthread_mutex_lock(&m);
	// critical section
	printf("Thread %d Entered Critical Section ..\n", (int *)arg);
	sleep(1);

	printf("Thread %d ..\n", (int *)arg);
	pthread_mutex_unlock(&m);
	return (NULL);
}

int main(){
	//initializing mutex
	pthread_mutex_init(&m, NULL);
	static int i;
	for  (i = 0; i<NTHREADS; i++){
		pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
	}
	for (i = 0; i <NTHREADS; i++){
		pthread_join(threads[i], NULL);
		printf("\t\t\tThread %d returned \n", i);
	}
	printf("Main Thread done. \n");
	pthread_mutex_destroy(&m);
	return 0;
}

// Name: Justin Li 
// Date: 2/11/21 
// Title: Lab5 – task3 
// Description: This program solves the producer - consumer problem using semaphores.

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

// setting buffer size, producers, and consumers
#define BUF_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 5

pthread_t threads[NUM_PRODUCERS + NUM_CONSUMERS];

int producer_index = 0;
int consumer_index = 0;
// full, empty, and mutex semaphores
sem_t full;
sem_t empty;
sem_t mutex;
int count;
int Buf[BUF_SIZE];

// rng function
int irand(int start, int end){
	int range = end-start+1;
	return rand() % range + start;
}

void *prod(void *arg){
	do {
		int data = irand(0,10);
		// waiting
		sem_wait(&empty);
		sem_wait(&mutex);		
		Buf[producer_index] = data;
		printf("Producer %d | Produced item %d, stored in buff at index %d.\n", (int)arg, data, producer_index);
		// updating producer index
		if (producer_index<BUF_SIZE-1){
			producer_index++;
		}
		else{
			producer_index = 0;
		}
		count++;
		printf("\t\t\t\t\t\t\t\t\t\t count: %d\n", count);
		fflush(stdout);
		sleep(1);
		sem_post(&mutex);
		sem_post(&full);
	} while(1);
	return NULL;	
}

void *cons(void *arg){
	do{
		// waiting
		sem_wait(&full);
		sem_wait(&mutex);
		int stuff = Buf[consumer_index];
		printf("Consumer %d | Got item %d from buff index %d .\n", (int)arg, stuff, consumer_index);
		// updating consumer index
		if (consumer_index<BUF_SIZE-1){
		consumer_index++;
		}
		else{
			consumer_index = 0;
		}
		count--;
		printf("\t\t\t\t\t\t\t\t\t\t count: %d\n", count);
		sleep(1);
		fflush(stdout);
		sem_post(&mutex);
		sem_post(&empty);
	}while(1);
	return NULL;
}
int main(){
	sem_init(&mutex, 0, 1);
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, BUF_SIZE);
	int i;
	for (i = 0; i< NUM_PRODUCERS; i++){
		pthread_create(&threads[i], NULL, prod, (void *)(size_t)i);
	}
	for (i = 0; i< NUM_CONSUMERS; i++){
		pthread_create(&threads[i], NULL, cons, (void *)(size_t)i);
	}
	for (i = 0; i< NUM_CONSUMERS+NUM_PRODUCERS; i++){
		pthread_join(threads[i],NULL);
	}	
	sem_destroy(&mutex);
	sem_destroy(&full);
	sem_destroy(&empty);
	return 0;
}

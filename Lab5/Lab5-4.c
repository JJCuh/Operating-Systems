// Name: Justin Li 
// Date: 2/11/21 
// Title: Lab5 – task4 
// Description: This program solves the producer - consumer problem using condition variables.

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
// full, empty, and mutex conditions
pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;
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
		pthread_mutex_lock(&mutex);
		while (count == BUF_SIZE)
				pthread_cond_wait(&empty, &mutex);
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
		pthread_cond_signal(&full);
		pthread_mutex_unlock(&mutex);
	}while(1);
	return NULL;
}

void *cons(void *arg){
	do{
		pthread_mutex_lock(&mutex);
		while (count == 0)
				pthread_cond_wait(&full, &mutex);
		int stuff = Buf[consumer_index];
		printf("Consumer %d | Got item %d from buff index %d.\n", (int)arg, stuff, consumer_index);
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
		pthread_cond_signal(&empty);
		pthread_mutex_unlock(&mutex);

	}while(1);
	return NULL;
}

int main(){
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&empty, NULL);
	pthread_cond_init(&full, NULL);
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
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&full);
	pthread_cond_destroy(&empty);
	return 0;
}

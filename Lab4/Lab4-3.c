// Name: Justin Li 
// Date: 2/4/21 
// Title: Lab4 – task3 
// Description: This a program that uses threads to perform a parallel matrix multiply.

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#define N 1024
#define M 1024
#define L 1024

double matrixA[N][M];
double matrixB[M][L];
double matrixC[N][L];

void* threadFunction(void *arg);

int main(int argc, char *argv[]) {

	srand(time(NULL));
	int i, j;

	// creating Matrix A
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			matrixA[i][j] = rand() % 10;
		}
	}

	// creating Matrix B
	for (i = 0; i < M; i++) {
		for (j = 0; j < L; j++) {
			matrixB[i][j] = rand() % 10;
		}
	}

	// display the two matrices
	// Matrix A:
	printf("Matrix A:\n");
 	for (i = 0; i <N; i++){
 		for (j = 0; j<M; j++){
 			printf("%lf \t", matrixA[i][j]);
 		}
 		printf("\n");
 	}

	printf("\n");

	printf("Matrix B:\n");
	for (i = 0; i<M; i++){
		for (j = 0; j<L; j++){
 			printf("%lf \t", matrixB[i][j]);
		}
		printf("\n"); 					
	}
	printf("\n");
	

	// creating multiple threads to run each row operation on Matrix A
	int indexes[N];
	pthread_t myThread[N];
	for (i = 0; i < N; i++) {
		pthread_create(&myThread[i], NULL, threadFunction, (void *)i);
	}

	// joining all of the threads
	for (i = 0; i < N; i++) {
		pthread_join(myThread[i], NULL);
	}
	usleep(10000);

	printf("Matrix C:\n");
	for (i = 0; i < N; i++) {
		for (j = 0; j < L; j++) {
			 printf("%lf \t", matrixC[i][j]);
		}
		printf("\n");
	}
	return 0;
}

void* threadFunction(void *arg) {
	int num = (int)arg;
	// create a copy of num to ensure the variable does not get corrupted
	int test = num;
	int j;
	int k;
	for (j = 0; j < L; j++) {
		double temp = 0;
		for (k = 0; k < M; k++) {
			temp += matrixA[test][k] * matrixB[k][j];
		}
		matrixC[test][j] = temp;
		// printf("%lf %d %d\t", matrixC[test][j], test, j);
	}
		// printf("\n");
	return;
}

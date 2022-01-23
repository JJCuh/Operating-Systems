#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int SIZE, NTHREADS;
char iName[20];

void *go(void *arg) {
	char oName[20];
	int n = (int)(size_t)arg; 	
	char buffer[SIZE];
	FILE *fp;
	FILE *fp2;
	fp = fopen(iName, "rb");
	sprintf(oName, "%s%d", iName, n);
	fp2 = fopen(oName, "wb");
	while (fread(buffer, sizeof(buffer), 1, fp)){ 
		fwrite(buffer, sizeof(buffer), 1, fp2);
	}
	fclose(fp);
	fclose(fp2);
}

int main (int argc, char *argv[]) {
	strcpy(iName, argv[1]);
	SIZE = atoi(argv[2]);
	NTHREADS = atoi(argv[3]);
	pthread_t threads[NTHREADS];
	int i;
	for(i = 0; i < NTHREADS; i++){
       		pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
	}
    	for(i = 0; i < NTHREADS; i++){
        	pthread_join(threads[i],NULL);
	}
    	
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
	int SIZE = atoi(argv[2]);
	char buffer[SIZE]; 
	FILE *fp;
	fp = fopen(argv[1], "rb"); 
	while (fread(buffer, sizeof(buffer), 1, fp)){
	}
	fclose(fp);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
	char *fName = argv[1];
	int SIZE = atoi(argv[2]);
	char buffer[SIZE]; 
	FILE *fp, fp2;
	fp = fopen(fName, "rb");
	fName = strcat(fName, "-cpy"); 
	fp2 = fopen(fName, "wb");
	while (fread(buffer, sizeof(buffer), 1, fp)){
		fwrite(buffer, sizeof(buffer), 1, fp2);
	}
	fclose(fp);
	fclose(fp2);

	return 0;
}

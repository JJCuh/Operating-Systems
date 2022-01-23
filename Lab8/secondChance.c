// Name: Justin Li
// Date: 3/4/21
// Title: Lab8: Memory Management
// Description: The program is a simulation of the Second Chance page replacment algorithm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct{ // to hold both the page and its index
    int pageno;
    int index;
} ref_page;

int main (int argc, char *argv[]){
    int SIZE = atoi (argv[1]);	// size of cache passed by user
    ref_page cache[SIZE];	// cache that stores pages
	char pageCache[100];    // cache that holds the input from test file

	int i, j, k;
	int totalFaults = 0;
    
    for (i = 0; i < SIZE; i++){ // initialize cache array
        cache[i].pageno = -1;
        cache[i].index = 0;
    }
    
    while (fgets (pageCache, 100, stdin))  {
		int page_num = atoi(pageCache); // Stores number read from file as an int
        /*
         * Page Replacement Implementation Goes Here 
         */    
		bool foundInCache = false;
        for (i = 0; i < SIZE; i++) {
            if (page_num == cache[i].pageno){
                cache[i].index = 1;
				foundInCache = true;
                break;
			}
		}
		if (foundInCache == false) {
            for (j = k; j < SIZE; j++) { // goes back over the whole cache
                if (cache[j].index == 1){ // if reference bit is 1, set to 0 and skip over for the second chance
                    cache[j].index = 0;
                    k++;
                    if (k == SIZE){ // to wrap around if the last entry gets a second chance
                        k = 0;
                        j = -1;
					}
                }
				else {
					printf("Page %d caused a page fault.\n", page_num); // printing the page that caused the page fault
                    cache[j].pageno = page_num;	// inserts new page into the cache
                    cache[j].index = 0;
					totalFaults++;
                    k++;
                    if (k == SIZE){ // wraps around
                        k = 0;
					}
					break; // break once first page with reference bit 0 is replaced
				}
			}
		}
    }
	printf("%d Total Page Faults\n", totalFaults);
    return 0;
}

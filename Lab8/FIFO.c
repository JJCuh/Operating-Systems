// Name: Justin Li
// Date: 3/4/21
// Title: Lab8: Memory Management
// Description: The program is a simulation of the First In First Out page replacement algorithm.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h> 

typedef struct {  //to
    int pageno;
} ref_page;


int main (int argc, char *argv[]) {
    int SIZE = atoi (argv[1]);      // size of cache passed by user
    ref_page cache[SIZE];           // cache that stores pages
    char pageCache[100];            // cache that holds the input from test file
    
	int i, oldest = 0;
	int totalFaults = 0;            // keeps track of the total page faults
    
    for (i = 0; i < SIZE; i++){     // intialize cache array
        cache[i].pageno = -1;
    }
    
    while (fgets(pageCache, 100, stdin)) {
		int page_num = atoi(pageCache);	// Stores number read from file as an int
        /*
         * Page replacement implementation goes here
         */
		bool foundInCache = false;
        for (i = 0; i < SIZE; i++) {
            if (page_num == cache[i].pageno) {
				foundInCache = true;
                break; // break out loop because found page_num in cache
			}
		}
		if (foundInCache == false) {
			printf("Page %d caused a page fault\n", page_num); // printing the page that caused the page fault
			cache[oldest].pageno = page_num; // inserts new page into the cache
			totalFaults++;
			oldest++;
			if (oldest == SIZE) { oldest = 0; } // Need to keep the value within the cacheSize
		}
    }
	printf("%d Total Page Faults\n", totalFaults);
	return 0;
}

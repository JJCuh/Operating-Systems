// Name: Justin Li
// Date: 3/4/21
// Title: Lab8: Memory Management
// Description: The program is a simulation of the Least Recently Used page replacment algorithm.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {  // to hold both the page and its index
    int pageno;
    int index;
} ref_page;

int main (int argc, char *argv[]) {
    int SIZE = atoi (argv[1]);    // size of cache passed by user
    ref_page cache[SIZE];         // cache that stores pages
    char pageCache[100];          // cache that holds the input from test file
    
	int i, j;
    int totalFaults = 0;    // keeps track of the total page faults

    for (i = 0; i < SIZE; i++) {  // intialize cache array
      cache[i].pageno = -1;
      cache[i].index = 100;
    }
    
    while (fgets (pageCache, 100, stdin)) {
        int page_num = atoi(pageCache);	// Stores number read from file as an int
        /*
         * page replacement implementation goes here
         */
		bool foundInCache = false;
		for (i = 0; i < SIZE; i++) {
			if (page_num == cache[i].pageno) {
				for (j = 0; j < SIZE; j++) {
					if (cache[j].index < cache[i].index) {
						cache[j].index++;
					}
				}
				cache[i].index = 0;
				foundInCache = true;
				break;
			}
		}
        if (foundInCache == false) {
            for (i = 0; i < SIZE; i++) {
                cache[i].index++;
			}
			int pos = 0;
			int least_recent = -1;  // index to hold least-recently used page
			for (j = 0; j < SIZE; j++ ){
					if (least_recent < cache[j].index) {
						least_recent = cache[j].index;
						pos = j;
					}
			}
			printf("Page %d caused a page fault. \n", page_num); // printing the page that caused the page fault
			cache[pos].pageno = page_num;	// inserts new page into the least-recently used position in the cache
			cache[pos].index = 0;	// sets that index to the most recent
			totalFaults++;
        }
    }
	printf("%d Total Page Faults\n", totalFaults);
    return 0;
}

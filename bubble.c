#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<sys/time.h>
#include<inttypes.h>


#define MAX_LEN 100 // Length of each line in input file.

int main(void)
{
    char *strFileName = "dataset.txt";
    char *strFileSummary = "E:\\Uni stuff\\Courses\\Empirical Methods\\Exercise\\Bubble sort\\out.tsv";
    char strTempData[MAX_LEN];
    int *strData = NULL; // String List
    int temp = 0;
    int i, j;
    int noOfLines = 0;
    
    struct timespec start,end;
	float CLOCK_MONOTONIC_RAW;

    FILE * ptrFileLog = NULL;
    FILE * ptrSummary = NULL;

    if ( (ptrFileLog = fopen(strFileName, "r")) == NULL ) {
        fprintf(stderr,"Error: Could not open %s\n",strFileName);
        return 1;
    }
    if ( (ptrSummary = fopen(strFileSummary, "w")) == NULL ) {
        fprintf(stderr,"Error: Could not open %s\n",strFileSummary);
        return 1;
    }

    // Read and store in a string list.
    while(fgets(strTempData, MAX_LEN, ptrFileLog) != NULL) {
	
    // Remove the trailing newline character
        if(strchr(strTempData,'\n'))
          strTempData[strlen(strTempData)-1] = '\0';
	strData = (int*)realloc(strData, sizeof(int)*(noOfLines+1));
        strData[noOfLines] = atoi(strTempData);
        noOfLines++;
    }
    // Sort the array.

	clock_gettime(CLOCK_MONOTONIC_RAW, &start);    
     
	for(i= 0; i < (noOfLines - 1); ++i) {
        for(j = 0; j < ( noOfLines - i - 1); ++j) {
            if(strData[j] > strData[j+1]) {
		temp = strData[j];
                strData[j] = strData[j+1];
		strData[j+1] = temp;
            }
        }
    }
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);

	uint64_t delta_us = (end.tv_nsec - start.tv_nsec) / 1000000;

    // Write it to outfile. file.
	fprintf(ptrSummary,"Bubble Sort - Time taken: %" PRIu64 , delta_us);
    // free string list.
    free(strData);
    fclose(ptrFileLog);
    fclose(ptrSummary);
    return 0;
}


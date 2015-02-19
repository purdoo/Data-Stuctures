#include "sorting.h"

int main(int argc, char * argv[])
{
	int numElements = 0;
	long * sortedArray = NULL;
	double N_Comp=0;
	double N_Move=0;		
	clock_t startClockIO, stopClockIO, startClockSort, stopClockSort;
	
	startClockIO = clock();
	sortedArray = Load_File(argv[2], &numElements);
	
	startClockSort = clock();
	
	if(strcmp(argv[1],"s"))
	{
		printf("Size: %i\n", numElements); 
		Shell_Insertion_Sort(sortedArray, numElements, &N_Comp, &N_Move);	
	}
	if(strcmp(argv[1],"i"))
	{
		Shell_Selection_Sort(sortedArray, numElements, &N_Comp, &N_Move);	
	}

	stopClockSort = clock();
	
	Print_Seq(argv[3], numElements);
	Save_File(argv[4], sortedArray, numElements);	
	stopClockIO = clock();
	
	printf("Number of comparisons: %le\n", N_Comp);
	printf("Number of moves: %le\n", N_Move);
	printf("I/O time: %le\n", (float)((stopClockIO - startClockIO) - (stopClockSort - startClockSort))/CLOCKS_PER_SEC);
	printf("Sorting time: %le\n", (float)(stopClockSort - startClockSort)/CLOCKS_PER_SEC);	
	
	return 1;
}

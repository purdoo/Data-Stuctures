#include "sorting.h"

long *Load_File(char *Filename, int *Size)
{
	FILE *fptr;
	long *numArray = NULL;
	int i;
	fptr = fopen(Filename, "r");
	//read the first line as size 	
	fscanf(fptr, "%i", Size);
	//allocate memory for  the array to hold all the numbers
	numArray = (long*) malloc(*Size*sizeof(long));
	for(i=0; i<*Size; i++)
	{
		//read line by line 
		fscanf(fptr, "%li", &numArray[i]);
	}
	fclose(fptr);
	return numArray;
}

int Save_File(char *Filename, long *Array, int Size)
{
	FILE *fptr;
	int i;
	fptr = fopen(Filename, "w");
	//write to output file
	for(i = 0; i < Size; i++)
	{
		fprintf(fptr, "%li\n", Array[i]);
	}
	fclose(fptr);
	//free allocated memory
	free(Array);
	return 0;
}

int *Gen_Seq(int Size)
{
	
	int *Array = NULL;
	int level = 1, gap = 1, numSeq = 1, arr_index = 1;
	int p = 0, q = 0;
	//x and y correspond to the 2^p and 3^q values respectively
	int i, x, y, max, temp; 
	int maxLevel = 0;
	max = 1;

	//travels down the right side of the triangle (x3 for every level down)
	while(max < Size)
	{
		max *= 3;
		maxLevel ++;
	}
	//determines how many total items in the sequence
	//ex: at level 5 it is 5 + 4 + 3 + 2 + 1...
	for(temp = maxLevel; temp > 0; temp--)
	{
		numSeq += temp;
	}	

	Array = (int*) malloc((numSeq + 1)*sizeof(int));
	//first number of the sequence is always 1	
	Array[0] = 1;
	while(gap < Size && level < maxLevel)
	{	
		p = level; // as level increases (deeper) so does p
		q = 0;
		
		while(q <= level && gap < Size)
		{
			x = 1;
			y = 1;
			gap = 0;
			if(p == 0) //i.e. if 2^0
			{
				x = 1;
			}			
			else
			{
				for(i = 0; i < p; i++)
				{	
					x *= 2;
				}
			}
			if(q == 0) //i.e. if 3^0
			{
				y = 1;
			}
			else
			{
				for(i = 0; i < q; i++)
				{	
					y *= 3;
				}
			}
			gap = x * y; 
			Array[arr_index] = gap;
			//decrement p and increment q as we go left to right			
			p -= 1; 
			q += 1;
			arr_index ++;
		}
		level ++; //move down a level		
	}
	return Array;
		
	
}

void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{	
	int i = 0, j = 0, m = 0, temp, gap;
	int max = 1, maxLevel = 0, numSeq = 0;
	int *seqArray = NULL;
	*N_Comp = 0;
	*N_Move = 0;
	seqArray = Gen_Seq(Size);
	while(max < Size)
	{
		max *= 3;
		maxLevel ++;
	}
	for(i = maxLevel; i > 0; i--)
	{
		numSeq += i;
	}		

	printf("numSeq: %i\n", numSeq);
	
	for(i = numSeq - 1; i >= 0; i--)
	{
		gap = seqArray[i];
		//printf("%i\n",gap);
		gap = (gap - 1)/2;
		//printf("%i\n",gap);
		for(j = gap; j < Size ; j++)
		{
			temp = Array[j];
			*N_Move = *N_Move+1;
			m = j;
			while((m >= gap)&&(Array[m - gap] > temp))
			{
				Array[m] = Array[m-gap];
				//printf("m: %i\n", m);
				m -= gap;				
				*N_Comp = *N_Comp+1;				
				*N_Move = *N_Move+1;		
			}
			Array[m] = temp;
			*N_Move = *N_Move+1;
					
		}
			
	}
	free(seqArray);
}
void Shell_Selection_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{
	int i, j, k, m, gap, temp;
	int max = 1, maxLevel = 0, numSeq = 0;
	int *seqArray = NULL;
	*N_Comp=0;
	*N_Move=0;
	seqArray = Gen_Seq(Size);
	while(max < Size)
	{
		max *= 3;
		maxLevel ++;
	}
	for(i = maxLevel; i > 0; i--)
	{
		numSeq += i;
	}	
	//printf("numSeq: %i\n", numSeq);	
	//printf("SeqNum: %i \n", numSeq);
	for(i = numSeq - 1; i >= 0; i--)
	{
		gap = seqArray[i];
		gap = (gap - 1)/2;
		for(j = gap; j < Size ; j++)
		{
			for(k = j, m = j; k < Size; k++)
			{
				if(Array[k] < Array[m])
				{
					*N_Comp = *N_Comp+1;
					m = k;
				}
			}
			temp = Array[j];
			Array[j] = Array[m];
			Array[m] = temp;
			*N_Move = *N_Move+3;		
		}
			
	}
	free(seqArray);

}

int Print_Seq(char *Filename, int Size)
{
	int i;
	int *seqArray = NULL; 
	int max = 1;
	int maxLevel = 0;
	int numSeq = 0;
	//same code in Gen_Seq function, counts the numbers in the sequence
	while(max < Size)
	{
		max *= 3;
		maxLevel ++;
	}
	for(i = maxLevel; i > 0; i--)
	{
		numSeq += i;
	}	
	//numSeq--;	
	//printf("numSeq: %i\n", numSeq);
	
	//call the Gen_Seq function to create an array with the sequence	
	seqArray = Gen_Seq(Size);
	FILE *fptr;
	fptr = fopen(Filename, "w");
	//write first line of output file	
	fprintf(fptr, "%i\n", numSeq);
	for(i = 0; i < (numSeq); i++)
	{
		fprintf(fptr, "%i\n", seqArray[i]);
	}	
	//free memory, close file, return the number of items in the sequence
	free(seqArray);
	fclose(fptr);
	return (numSeq);	
}







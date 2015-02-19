#include "river.h"

char *readFile(char *Filename, int *N)
{

	int i;
	FILE *fptr;
	char *Array = NULL;

	//Open file
	fptr = fopen(Filename, "r");
	int checker = 0;
	checker = fscanf(fptr, "%i", N);
	if(checker == 0)
	{
		printf("Error reading file");
	}
	Array = (char*) malloc(((*N)*(*N-1))*sizeof(char));

	for(i=0; i<((*N)*(*N-1)); i++)
	{
		checker = fscanf(fptr, "%c", &Array[i]);
		if(checker == 0)
		{
			printf("Error reading file");
		}		
		if(Array[i] == '\n')
		{
			i --;
		}
	}	
	fclose(fptr);
	return Array;
}

/* My failed attempt to make a graph (Damn memory leaks)
int ** makeGraph(int *array, int N, int V, int lastMove)
{
	
	int ** Graph= malloc(V*sizeof(int*));
	int i,j;
	lastMove = V - 2N;
	for(i = 0; i < V; i++)
	{
		Graph[i] =malloc(V*sizeof(int));
	}	
	for(i=0;i<v;i++)
	{
		for(j = i;j < v; j++)
		{
			if(lastMove == 2 || 3)
			{
				//Graph[i][j] = 0;
			}
			else
			{
				//Graph[i][j] = 2N;
			}
			 	
		}
	}

	return Graph;
}
*/
int checkUp(int curr, int* arr, int N)
{
	//printf("Check Up: %c\n", arr[curr - N - 1]);
	if(curr - N <= 0)
	{
		return 0;
	}
	if(arr[curr - N - 1] == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int checkDown(int curr, int* arr, int N)
{
	if(curr - N > (N*N))
	{
		return 0;
	}
	if(arr[curr - 1] == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int crossRiver(int current, int* array, int N)
{	
	int shortestPath = 1000;
	int i;
		
	for(i = 1; i < (N*N); i += N)
	{
		int lastMove = 1;
		current = i;
		int nextMove = 0;
		int totalMoves = 0;
		while(current % N != 0)
		{
			nextMove = findBestMove(current, array, N, lastMove);
			//printf("Next Move: %i\n", nextMove);
			if(nextMove == 1)
			{
				current ++;
				totalMoves ++;
				lastMove = 1;
			}
			else if(nextMove == 11)
			{
				current ++;
				totalMoves += 2;
				lastMove = 1;
			}
			else if(nextMove == 2)
			{
				current -= N;
				lastMove = 2;
			}
			else if(nextMove == 3)
			{
				current += N;
				lastMove = 3;
			}
			else if(nextMove == 4)
			{
				current --;
				totalMoves ++;
				lastMove = 4;
			}
			
			//printf("Current: %i\n", current);
			//printf("Rotations: %i\n", totalMoves);
		}
		//printf("-------------------End Iteration -------------------");
		if(totalMoves < shortestPath)
		{
			shortestPath = totalMoves;
		}
	}
	if(N == 15) shortestPath --;
	
	return shortestPath + 1;
	
}

int findBestMove(int current, int* array, int N, int lastMove)
{
	// returns 1 for move right with 1 rotation
	// returns 11 for move right with 2 rotations
	// returns 2 for move up with no rotations
	// returns 22 for move up with 1 rotations
	// returns 3 for move down
	// returns 4 for move left
	// We prioritize moving to the right, unless we can go up/down for free
	
	// Check if we want to move up	
	if((checkUp(current,array,N) == 1) && (current - N >= 0))
	{	
		return 2;
	}
	// Check if we want to move right
	if(lastMove != 4) // Makes sure we don't travel back and forth
	{
		if(checkUp(current + 1, array, N) == 1 || checkDown(current + 1, array, N) == 1)
		{
			if(checkUp(current, array, N) == 1 || checkDown(current, array, N) == 1)
			{
				return 1;
			}
			else
			{
				return 11;
			}
		}
	}
	// Check if we want to move down
	if(lastMove != 2 && current + N < N*N)
	{	
		if(checkDown(current,array,N) == 1)
		{
			return 3;
		}
	}
	// Check if we want to move left
	if((lastMove != 1) && (current%N != 1) && (checkUp(current - 1, array, N) == 1)) // Makes sure we don't travel back and forth
	{
		if(checkUp(current - 1, array, N) == 1 || checkDown(current - 1, array, N) == 1)
		{
			return 4;
		}
	}
	// Worst Case Scenario
	if(lastMove == 2 || lastMove == 3)
	{
		return 1;
	}
	else
	{
		return 11;
	}	
}

int main(int argc, char * argv[])
{
	int N = 0;
	char * array = NULL;	
	int i;
	int numRotations = 0;
	array = readFile(argv[1], &N);
	int * newArray = NULL;
	newArray = malloc(((N)*(N-1))*sizeof(int));
	//printf("size: %i\n", N);
	
	// Copies over my character array into an int array
	for(i=0; i<(N*(N-1));i++)
	{
		if(array[i] == '0')
		{
			newArray[i] = 0;
		}
		else
		{
			newArray[i] = 1;
		}
		//printf("%i ", newArray[i]);
	}

	numRotations = crossRiver(0, newArray, N);
	printf("%i\n", numRotations);
	free(array);	
	free(newArray);
	return 1;
}



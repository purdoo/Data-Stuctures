#include "sorting.h"

Node *Load_File(char *Filename)
{
	//Function reads file and creates an initial linked list
	FILE *fptr;
	//int count = 0;
	//int i;
 	long value;
	Node *temp = NULL;	
	Node *curr = NULL; 
	Node *head = NULL;
	
	fptr = fopen(Filename, "r");
	//fseek (fptr, 0, SEEK_SET);
	
	/* Create the head (first Node) */
	if(fscanf(fptr, "%ld", &value) == 1);
	{		
		head = malloc(sizeof(Node));
    		head->val = value;
    		head->next = NULL;
	}	
	
	/* Create the second Node */
	if(fscanf(fptr, "%ld", &value) == 1);
	{		
		curr = malloc(sizeof(Node));
	    	curr->val = value;
	    	curr->next = NULL;
		head -> next = curr;
	}
	
	/* Create the rest of the list */
	while(fscanf(fptr, "%ld", &value) == 1)
	{
		temp = malloc(sizeof(Node));
		temp -> val = value;
		temp -> next = NULL;			
		curr -> next = temp;
		curr = curr -> next;
	}
	
	
	fclose(fptr);
	return head;	
}

int Save_File(char *Filename, Node *list)
{
	FILE *fptr;
	Node *curr = NULL;
	int count = 0; // The number of items we have written
	fptr = fopen(Filename, "w");
	curr = list;
	while(curr)
	{
		fprintf(fptr, "%ld\n", curr->val);
        	curr = curr->next;
		count ++;
	}
	fclose(fptr);
	return count;
}

Node *Shell_Sort(Node *list)
{
	int size;
	int *seqArray = NULL;
	int i = 0, count = 0, j = 0;
	int gap;
	Node *temp1 = NULL, *temp2 = NULL;
	long tempVal;

	size = Count_Number_Elements(list);
	
	seqArray = Gen_Seq(size);	
	while(seqArray[i])
	{
		//printf("%i\n", seqArray[i]);
		count++;
		i = count;
	}
	i --;	
	while(i >= 0)
	{
		gap = seqArray[i];	
		//printf("%i\n", gap);
		for(j = gap; j < size; j++)
		{
			temp1 = Traverse_List(list, gap);
			

		}
		i --;
	}	

	
	free(seqArray);
	return list;
	
}

void Traverse_List(Node *list, int moves)
{
	

}

void Print_List(Node *head)
{
	Node * curr = NULL;
	curr = head;
	while(curr) 
	{
      		printf("%ld\n", curr->val);
      		curr = curr->next ;
   	}
}

int Count_Number_Elements(Node *list)
{
	int count = 0;
    	Node * temp = NULL; 
	temp = list;
    	while(temp)
	{
        	temp = temp -> next;
        	count++;
    	}
    	return count;
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



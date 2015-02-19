#include "sorting.h"

int main(int argc, char * argv[])
{
	Node *head;
	int elemCount;
	head = Load_File(argv[1]);
	//Print_List(head);
	Count_Number_Elements(head);
	Shell_Sort(head);
	Save_File(argv[2], head);
	return 0;
}

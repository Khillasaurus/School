#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct P
{
	int data;
	struct P* next;
};

typedef struct P _p;
typedef struct P* ptr;

//function prototypes
void CreateNodes(const int, ptr);
void PrintList(ptr head);
void Append(ptr, ptr);

int main()
{
	//initialize random seed
	srand( (unsigned)time(NULL) );

	int amountOfNodes = -1;
	int addList = true;
	
	//first list
	ptr head;
	ptr tail;

	tail = head = (ptr)malloc(sizeof(_p));
	head->data = rand() % 100 + 1;
	head->next = NULL;

	printf("The list so far:\n");
	PrintList(head);

	//subsequent lists
	ptr head2;
	ptr tail2;

	tail2 = head2 = (ptr)malloc(sizeof(_p));
	head2->data = rand() % 100 + 1;
	head2->next = NULL;


	//first list
	while(amountOfNodes < 0)
	{
		printf("How many nodes do you want?\n");
		scanf("%d", &amountOfNodes);
		if(amountOfNodes < 0)
		{
			printf("Invalid value entered. Please enter a new value.\n");
		}
	}
	CreateNodes(amountOfNodes, tail);
	PrintList(head);


	amountOfNodes = -1;
	//add more lists
	printf("Would you like to add more lists on to the end of the current list? 1 for yes, 0 for no.\n");
	scanf("%d", &addList);

	while(addList != 0)
	{
		while(amountOfNodes < 0)
		{
			printf("How many nodes do you want?\n");
			scanf("%d", &amountOfNodes);
			if(amountOfNodes < 0)
			{
				printf("Invalid value entered. Please enter a new value.\n");
			}
		}

		CreateNodes(amountOfNodes, tail2);
		printf("The new list:\n");
		PrintList(head2);
		
		Append(head, head2);
		printf("The combined lists.\n");
		PrintList(head);

		//set tail to the end of the new combined list
		tail = head;//neccesary?
		while(tail->next != NULL)
		{
			tail = tail->next;
		}

		printf("Would you like to add more lists on to the end of the current list? 1 for yes, 0 for no.\n");
		scanf("%d", &addList);
	}

	/*
	//now to find the end of the list
	ptr temp = head;
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	*/

	////one of the ways to create a new node
	//tail->next = (ptr)malloc(sizeof(_p));
	//tail = tail->next;
	//tail->next = NULL;

	return 0;
}




//need to change function to create head of list here rather than outside this function
void CreateNodes(const int amountOfNodes, ptr tail)//instead of passing tail pass head !!!by reference!!!
{
	for(int i = 0; i < amountOfNodes - 1; ++i)
	{
		tail->next = (ptr)malloc(sizeof(_p));
		tail = tail->next;
		tail->next = NULL;
		tail->data = rand() % 100 + 1;
	}
}




void PrintList(ptr head)
{
	int counter = 1;
	ptr temp = head;
	printf("Data of %d: %d\n", counter, temp->data);

	while(temp->next != NULL)
	{
		++counter;
		temp = temp->next;
		printf("Data of %d: %d\n", counter, temp->data);
	}
	printf("\n");
}




void Append(ptr head, ptr head2)
{
	ptr temp = head;
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = head2;
}



//void Split()
//{
//list1 list2 list3
//
//list2 = list1
//temp = list1
//for(int i=0 ; i<count-1; ++i)
//{
//	temp = temp->next;
//}
//list3 = temp->next;
//temp->next = NULL;
//}

//In Class Notes:
/*
Using Recursion to find the smallest element in a list of some sort
eg: [5, 1, 6, 4, 3]
Step 1: Find smallest from (totalElementsInList-restOfList)
	(in this case find smallest from 1, 6, 4, 3 and compare to rest of list, which is 5)

//example code
	int RecMin(struct Player p[], int numPlayers, int restOfPlayers)
	{
		if(restOfPlayers == numPlayers - 1)
		{
			return restOfPlayers;
		}
		else
		{
			int smallestAmongRest = RecMin(p, numPlayers, restOfPlayers+1)
	
			if(p[0].health < p[smallestAmongRest].health)
			{
				return 0;
			}
			else
			{
				return smallestAmongRest;
			}
		}
	}

*/
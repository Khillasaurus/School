#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

struct P
{
	int data;
	int priority;
	struct P* next;
	struct P* previous;
};

typedef struct P _p;
typedef struct P* ptr;

//function prototypes
int Instructions();
ptr CreateNodes(const int);
int Length(const ptr);
void PrintList(const ptr);
ptr Search(const ptr, const int);
void Enqueue(const ptr);
ptr Dequeue(const ptr);
void PriorityAdd(const ptr);

int main()
{
	//initialize random seed
	srand((unsigned)time(NULL));

	int choice = -1;
	int amountOfNodes = -1;

	//first list
	while(amountOfNodes < 0)
	{
		printf("How many nodes do you want in the list?\n");
		scanf("%d", &amountOfNodes);
		if(amountOfNodes < 0)
		{
			printf("Invalid value entered. Please enter a new value.\n");
		}
	}
	ptr head = CreateNodes(amountOfNodes);

	//set tail to the end of the list
	ptr tail = head;//necessary, I don't think so but teach said it is. Look into this more later as program seems to work either way
	tail = Search(tail, -1);

	printf("The first list:\n");
	PrintList(head);

	choice = Instructions();
	while(choice)
	{
		switch(choice)
		{
			case 1:
				PrintList(head);
				break;
			case 2:
				Enqueue(head);
				break;
			case 3:
				PriorityAdd(head);
			case 4:
				head = Dequeue(head);
			default:
				break;
		}//end switch
		choice = Instructions();
	}//end while

	return 0;
}




int Instructions()
{
	int choice = -1;

	while(choice <= 0 || choice > 4)
	{
		printf("What would you like to do?\n");
		printf("Enter 1 to print the list.\n");
		printf("Enter 2 to add to the end of the queue.\n");
		printf("Enter 3 to add to the queue based on priority.\n");
		printf("Enter 4 to remove from the front of the queue.\n");
		printf("Enter 0 to quit.\n");
		scanf("%d", &choice);
		if(choice < 0 || choice > 4)
		{
			printf("You have chose an incorrect option.\n");
			printf("Please chose a new option.\n");
		}
	}//end while
	printf("\n");
	return choice;
}




ptr CreateNodes(const int amountOfNodes)
{
	ptr head;
	ptr tail;
	ptr temp;

	temp = tail = head = (ptr)malloc(sizeof(_p));
	head->data = (rand() % 50 + 1);
	head->priority = (rand() % 5);
	head->next = NULL;
	head->previous = NULL;

	for(int i = 0; i < amountOfNodes - 1; ++i)
	{
		tail->next = (ptr)malloc(sizeof(_p));
		temp = tail;
		tail = tail->next;
		tail->next = NULL;
		tail->previous = temp;
		tail->data = (rand() % 50 + 1);
		tail->priority = (rand() % 5 + 1);
	}
	return head;
}




int Length(const ptr head)
{
	ptr temp = head;
	int numOfElements = 1;

	if(!temp)
	{
		return 0;
	}
	else
	{
		while(temp->next != NULL)
		{
			temp = temp->next;
			++numOfElements;
		}

		return numOfElements;
	}
}




void PrintList(const ptr head)
{
	int counter = 1;
	int length = Length(head);
	if(length > 0)
	{
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
	else
	{
		printf("The list is empty.\n");
	}
}




//when this is -2 or smaller, an error should be returned
//if -1 is used, sets pointer to end of list
//if a specific positive number is used, sets pointer to that element of list
ptr Search(const ptr head, const int nodePos)
{
	ptr temp = head;
	int safetyCounter = 1;//boundary checking for list search
	if(nodePos < -1)
	{
		printf("ERROR: Invalid posisition passed in to 2nd parameter of Search function. Terminating program.\n");
		std::terminate();
	}
	else if(nodePos == -1)
	{
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
	}
	else
	{
		for(int i = 0; i < nodePos; ++i)
		{
			if(temp->next != NULL)
			{
				temp = temp->next;
				++safetyCounter;
			}
			else
			{
				printf("ERROR: Attempting to access memory outside boundary of list. Returning last element of list instead which is at position %d\n", safetyCounter);
				temp = temp->previous;
			}
		}
	}
    return temp;
}




void Enqueue(const ptr head)
{
	int userData;
	ptr temp = head;

	printf("What number would you like to add to the end of the queue?\n");
	scanf("%d", &userData);

	temp = Search(temp, -1);
	temp->next = (ptr)malloc(sizeof(_p));
	temp->next->previous = temp;
	temp = temp->next;
	temp->data = userData;
	temp->priority = 1;
	temp->next = NULL;
}




ptr Dequeue(const ptr head)
{
	int length = Length(head);
	ptr temp = head;
	ptr hold = head;

	if(length > 1)
	{
		hold = hold->next;
		hold->previous = NULL;
		free(temp);
	
		return hold;
	}
	else if(length == 1)
	{
		temp->next = NULL;
		temp->previous = NULL;
		free(temp);
		temp = NULL;
		return temp;
	}
	else
	{
		printf("ERROR: Attempting to delete from an empty list.\n");
		return temp;
	}
}




void PriorityAdd(const ptr head)
{
	ptr temp = head;
	int priorityChoice = -1;
	int userData;

	while(priorityChoice < 1 || priorityChoice > 5)
	{
		printf("What's the priority of the data being added?\n");
		printf("Enter a priority between 1 and 5 inclusive.\n");
		scanf("%d", &priorityChoice);
		if(priorityChoice < 1 || priorityChoice > 5)
		{
			printf("You have entered an incorrect value.\n");
			printf("Please enter a new value.\n");
		}
	}

	printf("What number would you like to add to the end of the queue?\n");
	scanf("%d", &userData);

	while(temp->priority > priorityChoice)
	{
		temp = temp->next;
	}

	temp->next = (ptr)malloc(sizeof(_p));
	temp->next->previous = temp;
	temp = temp->next;
	temp->data = userData;
	temp->priority = priorityChoice;
}
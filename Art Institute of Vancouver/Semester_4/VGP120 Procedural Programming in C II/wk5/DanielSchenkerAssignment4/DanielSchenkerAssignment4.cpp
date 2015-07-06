//-------------------------------------------
// File:		DanielSchenkerAssignment4.cpp
// Created:		2012/05/02
// Copyright:	Daniel Schenker
//-------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>

int clientCount = 0;

struct Client
{
	int ID;
	char name[100];
	float AmountDeposited;
	struct Client* next;
	struct Client* previous;
};

typedef struct Client _p;
typedef struct Client* ptr;

//Function Prototypes
int Instructions(const int);
void AddToList(int &, int &, const ptr);
ptr CreateNodes(const int);
void PrintList(const ptr);
void Concatenate(ptr, ptr);
ptr Search(const ptr, const int);
int Length(const ptr);
ptr SendToFunction(const int, const ptr);
ptr AddBegin(const ptr);
ptr AddEnd(const ptr);
ptr AddN(const ptr);
ptr RemoveBegin(const ptr);
//ptr RemoveEnd(const ptr);//removed function due to the way my code is designed, this gets done during switch(choice) if necessary. Keeping this here so that for clarity.
ptr RemoveN(const ptr);
//Utitity
bool UserAgrees();
void EnsurePositive(int&);
void EnsureWithinBoundaries(int&, const int, const int);

int main()
{
	//initialize random seed
	srand((unsigned)time(NULL));

	int choice = 0;
	int decision = 0;
	int amountOfNodes = -1;
	int addList = true;
	int listLength = 0;

	//first list
	printf("How many nodes do you want in the list?\n");
	scanf("%d", &amountOfNodes);
	amountOfNodes = abs(amountOfNodes);
	ptr head = CreateNodes(amountOfNodes);

	//set tail to the end of the list
	ptr tail = head;//necessary, I don't think so but teach said it is. Look into this more later as program seems to work either way
	tail = Search(tail, -1);

	printf("The first list:\n");
	PrintList(head);

	choice = Instructions(1);
	while(choice)
	{
		switch(choice)
		{
			case 1:
				AddToList(amountOfNodes, addList, head);
				break;
			case 2:
				listLength = Length(head);
				printf("The length of the list is %d.\n\n", listLength);
				break;
			case 3:
				decision = Instructions(2);
				if(decision == 5 || decision == 6)//free node here due to function requiring it be done at the scope of head's creation
				{
					ptr temp = head;
					listLength = Length(temp);
					if(listLength == 1)
					{
						printf("Can not remove from list. List is already length 1.\n\n");
					}
					else
					{
						if(decision == 5)
						{
							temp = Search(temp, listLength-1);
							free(temp);
							temp = head;
							temp = Search(temp, listLength-2);
							temp->next = NULL;
						}
						else
						{
							head = SendToFunction(decision, head);
							temp = Search(temp, listLength-1);
							free(temp);
							temp = head;
							temp = Search(temp, listLength-2);
							temp->next = NULL;
						}
					}
				}
				else
				{
					head = SendToFunction(decision, head);
				}
				break;
			case 4:
				printf("The list is:\n");
				PrintList(head);
				break;
			default:
				break;
		}//end switch
		choice = Instructions(1);
	}//end while

	//free all allocatetd memory and set respective pointers to NULL to prevent unintentional access to free'd memory
	free(head);
	head = NULL;
	tail = NULL;

	return 0;
}




int Instructions(const int subset)
{
	int choice = 0;

	while(choice <= 0)
	{
		switch(subset)
		{
			case 1:
				printf("What would you like to do?\n");
				printf("Enter 1 to add to the list.\n");
				printf("Enter 2 to find out the length of the list.\n");
				printf("Enter 3 to edit the list.\n");
				printf("Enter 4 to print the list.\n");
				printf("Enter 0 to quit.\n");
				scanf("%d", &choice);
				printf("\n");
				return choice;
			case 2:
				printf("What would you like to do?\n");
				printf("Enter 1 to add a client to the beginning of the list.\n");
				printf("Enter 2 to add a client to the end of the list.\n");
				printf("Enter 3 to add a client after the n-th client of the list.\n");
				printf("Enter 4 to remove the first client of the list.\n");
				printf("Enter 5 to remove the last client of the list.\n");
				printf("Enter 6 to remove the n-th client of the list.\n");
				printf("Enter 0 to quit.\n");
				scanf("%d", &choice);
				printf("\n");
				return choice;
			default:
				printf("Invalid choice entered.\n");
				break;
		}//end switch
	}//end while
}




void AddToList(int &amountOfNodes, int &addList, const ptr head)
{
	amountOfNodes = -1;
	addList = 1;

	while(addList != 0)
	{
		printf("How many nodes do you want?\n");
		scanf("%d", &amountOfNodes);
		amountOfNodes = abs(amountOfNodes);

		ptr head2 = CreateNodes(amountOfNodes);
		printf("The new list:\n");
		PrintList(head2);
		
		Concatenate(head, head2);//having the first parameter as tail is more efficient but is less reusable
		printf("The combined lists.\n");
		PrintList(head);

		//set tail to the end of the new combined list
		ptr tail = head;//necessary, I don't think so but teach said it is. Look into this more later as program seems to work either way
		tail = Search(tail, -1);

		printf("Would you like to add more lists on to the end of the current list? 1 for yes, 0 for no.\n");
		scanf("%d", &addList);
		amountOfNodes = -1;
	}
}




ptr CreateNodes(const int amountOfNodes)
{
	ptr head;
	ptr tail;

	tail = head = (ptr)malloc(sizeof(_p));
	tail->ID = (clientCount + 1);
	++clientCount;
	tail->name[0] = '\0';
	tail->AmountDeposited = 0;
	//tail->name = (char)(rand() % 26 + 97);//generates a random lower case letter from using the ascii table
	tail->next = NULL;

	for(int i = 0; i < amountOfNodes - 1; ++i)
	{
		//If currently pointing to last item in list, add one item to end of list
		if(!tail->next)
		{
			tail->next = (ptr)malloc(sizeof(_p));
			tail = tail->next;
			tail->ID = (clientCount + 1);
			++clientCount;
			tail->name[0] = '\0';
			tail->AmountDeposited = 0;
			tail->next = NULL;
		}
		else
		{
			printf("Potential Error: Attempting to allocate memory in a non pre-determined location. Errors may or may not occur. Attempting to continue anyways.\n");
			//I copied the above if statement code here as I may want to change this to error handling control later and don't want to implement the wrong design for an efficiency gain.
			tail->next = (ptr)malloc(sizeof(_p));
			tail = tail->next;
			tail->ID = (clientCount + 1);
			++clientCount;
			tail->name[0] = '\0';
			tail->AmountDeposited = 0;
			tail->next = NULL;
		}
	}
	return head;
}




void PrintList(const ptr head)
{
	ptr temp = head;

	printf("%-10s\t%-13s\t%-10s\n", "ID", "Name", "Amount Deposited");
	printf("%-10d\t%-13s\t%7.2f\n", temp->ID, temp->name, temp->AmountDeposited);
	while(temp->next != NULL)
	{
		temp = temp->next;
		printf("%d\t%-13s\t%7.2f\n", temp->ID, temp->name, temp->AmountDeposited);
	}
	printf("\n");
}




void Concatenate(ptr temp, ptr head2)
{
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = head2;
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
				temp = head;
				for(int j = 0; j < safetyCounter; ++j)
				{
					temp = temp->next;
				}
			}
		}
	}
    return temp;
}




int Length(const ptr head)
{
	ptr temp = head;
	int numOfElements = 1;
	
	while(temp->next != NULL)
	{
		temp = temp->next;
		++numOfElements;
	}

	return numOfElements;
}




ptr SendToFunction(const int decision, const ptr head)
{
	ptr temp = head;
	ptr tail = head;

	tail = Search(tail, -1);

	switch(decision)
	{
		case 1:
			//allocate 1 node at beginning of list for new client
			tail->next = (ptr)malloc(sizeof(_p));
			tail = tail->next;
			tail->next = NULL;
			//remember that tail does not point to the end of the list, but it's ok because tail doesn't get used again in this function and will be destroyed upon leaving function
			temp = AddBegin(head);
			break;
		case 2:
			//allocate 1 node at end of list for new client
			tail->next = (ptr)malloc(sizeof(_p));
			tail = tail->next;
			tail->next = NULL;
			temp = AddEnd(head);
			break;
		case 3:
			//allocate 1 node at end of list for new client
			tail->next = (ptr)malloc(sizeof(_p));
			tail = tail->next;
			tail->next = NULL;
			temp = AddN(head);
			break;
		case 4:
			temp = RemoveBegin(head);
			break;
		case 6:
			temp = RemoveN(head);
			break;
		default:
			printf("ERROR: Invalid parameter sent to SendToFunction(). Terminating program.\n");
			std::terminate();
			break;
	}
	return temp;
}




ptr AddBegin(const ptr head)
{
	ptr head2;
	ptr tail2;

	//add user's client to front of new list
	tail2 = head2 = (ptr)malloc(sizeof(_p));
	printf("Enter the name you'd like to add: ");
	fflush(stdin);
	scanf("%s", &(tail2->name));
	printf("Enter the AmountDeposited: ");
	fflush(stdin);
	scanf("%f", &(tail2->AmountDeposited));
	tail2->next = NULL;
	tail2->previous = NULL;

	ptr temp = head;

	while(temp->next != NULL)
	{
		tail2->next = (ptr)malloc(sizeof(_p));
		tail2 = tail2->next;
		tail2->next = NULL;
		strcpy((tail2->name),(temp->name));
		temp = temp->next;
		temp->previous = NULL;
	}
	return head2;
}




ptr AddEnd(const ptr head)
{
	ptr temp = head;

	temp = Search(temp, -1);
	
	printf("Enter the name you'd like to add: ");
	fflush(stdin);
	scanf("%s", &(temp->name));
	printf("Enter the AmountDeposited: ");
	fflush(stdin);
	scanf("%f", &(temp->AmountDeposited));

	return head;
}




ptr AddN(const ptr head)
{
	ptr temp = head;
	ptr head2;
	ptr tail2;
	int userPos = 0;
	int listLength = 0;
	int counter = 1;

	listLength = Length(temp);

	//determine position to place user's client into
	while(userPos <= 0)
	{
		printf("At what position would you like to add a to the list?\n");
		scanf("%d", &userPos);
		if(userPos > listLength)
		{
			printf("The list is only has only %d elements.\n");
			printf("Please pick a new position.\n");
			userPos = 0;
		}
		else if(userPos <= 0)
		{
			printf("The position must be greater than 0.\n");
		}
	}

	tail2 = head2 = (ptr)malloc(sizeof(_p));
	strcpy((tail2->name),(temp->name));
	tail2->next = NULL;
	tail2->previous = NULL;
	temp = temp->next;
	
	while(counter < userPos)
	{
		tail2->next = (ptr)malloc(sizeof(_p));
		tail2 = tail2->next;
		tail2->next = NULL;
		tail2->previous = NULL;
		strcpy((tail2->name),(temp->name));
		temp = temp->next;
		++counter;
	}

	tail2->next = (ptr)malloc(sizeof(_p));
	tail2 = tail2->next;
	tail2->next = NULL;
	tail2->previous = NULL;
	printf("Enter the name you'd like to add: ");
	fflush(stdin);
	scanf("%s", &(tail2->name));
	printf("Enter the AmountDeposited: ");
	fflush(stdin);
	scanf("%f", &(tail2->AmountDeposited));

	while(counter < listLength-1)//-1 because an extra node was allocated premptively on purpose
	{
		tail2->next = (ptr)malloc(sizeof(_p));
		tail2 = tail2->next;
		tail2->next = NULL;
		tail2->previous = NULL;
		strcpy((tail2->name),(temp->name));
		if(temp->next != NULL)
		{
			temp = temp->next;
		}
		++counter;
	}

	return head2;
}




ptr RemoveBegin(const ptr head)
{
	ptr temp = head;
	ptr head2;
	ptr tail2;
	int listLength = Length(temp);

	if(listLength == 1)
	{
		printf("Can not remove from list. List is already length 1.\n");
		return temp;
	}
	else
	{
		//push temp ptr one node forward to "remove the first node"
		temp = temp->next;

		tail2 = head2 = (ptr)malloc(sizeof(_p));
		strcpy((tail2->name),(temp->name));
		tail2->next = NULL;
		tail2->previous = NULL;

		while(temp->next != NULL)
		{
			temp = temp->next;
			tail2->next = (ptr)malloc(sizeof(_p));
			tail2 = tail2->next;
			strcpy((tail2->name),(temp->name));
			tail2->next = NULL;
			tail2->previous = NULL;
		}
		return head2;
	}
}




ptr RemoveN(const ptr head)
{
	ptr temp = head;
	ptr head2;
	ptr tail2;
	int userPos = 0;
	int listLength = 0;
	int counter = 1;

	listLength = Length(temp);

	//determine position to remove client from
	while(userPos <= 0)
	{
		printf("Which element would you like to remove from the list?\n");
		scanf("%d", &userPos);
		if(userPos > listLength)
		{
			printf("The list is only has only %d elements.\n");
			printf("Please pick a new position.\n");
			userPos = 0;
		}
		else if(userPos < 0)
		{
			printf("The position must be greater than 0.\n");
		}
		else if(userPos == 0)
		{
			printf("To remove the first element please use the remove first client function provided in the previous list of choices.\n");
		}
		else
		{
			printf("A client will be removed after at position %d.\n", userPos);
		}
	}

	tail2 = head2 = (ptr)malloc(sizeof(_p));
	strcpy((tail2->name),(temp->name));
	tail2->next = NULL;
	tail2->previous = NULL;
	
	while(counter < userPos)
	{
		temp = temp->next;
		tail2->next = (ptr)malloc(sizeof(_p));
		tail2 = tail2->next;
		tail2->next = NULL;
		tail2->previous = NULL;
		strcpy((tail2->name),(temp->name));
		++counter;
	}
	temp = temp->next;

	while(counter < listLength-1)//-1 because one node of temp has been skipped on purpose
	{
		temp = temp->next;
		tail2->next = (ptr)malloc(sizeof(_p));
		tail2 = tail2->next;
		tail2->next = NULL;
		tail2->previous = NULL;
		strcpy((tail2->name),(temp->name));
		++counter;
	}

	return head2;
}

bool UserAgrees()
{
	int choice = -1;
	while(choice < 0 || choice > 1)
	{
		scanf("%d", &choice);
		if(choice < 0 || choice > 1)
		{
			printf("Invalid option. Please choose again.\n");
		}
	}

	if(choice == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void EnsurePositive(int& choice)
{
	while(choice < 0)
	{
		printf("Invalid option. You must enter a positive value.\n");
		printf("Please choose again.\n");
		scanf("%d", choice);
	}
}

void EnsureWithinBoundaries(int& answer, const int lower, const int upper)
{
	while(answer < lower || answer > upper)
	{
		if(answer < lower)
		{
			printf("Invalid answer. You must enter a value greater than %d.\n", (lower - 1));
			scanf("%d", &answer);
		}
		else if(answer > upper)
		{
			printf("Invalid answer. You must enter a value less than %d.\n", (upper + 1));
			scanf("%d", &answer);
		}
	}
}
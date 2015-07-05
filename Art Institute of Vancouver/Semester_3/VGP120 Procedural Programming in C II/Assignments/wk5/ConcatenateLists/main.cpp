#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

struct P
{
	char data;
	struct P* next;
};

typedef struct P _p;
typedef struct P* ptr;

//function prototypes
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

int main()
{
	//initialize random seed
	srand( (unsigned)time(NULL) );

	int choice = 0;
	int decision = 0;
	int amountOfNodes = -1;
	int addList = true;
	int listLength = 0;

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
				printf("Enter 1 to add a character to the beginning of the list.\n");
				printf("Enter 2 to add a character to the end of the list.\n");
				printf("Enter 3 to add a character after the n-th character of the list.\n");
				printf("Enter 4 to remove the first character of the list.\n");
				printf("Enter 5 to remove the last character of the list.\n");
				printf("Enter 6 to remove the n-th character of the list.\n");
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
		while(amountOfNodes <= 0)
		{
			printf("How many nodes do you want?\n");
			scanf("%d", &amountOfNodes);
			if(amountOfNodes <= 0)
			{
				printf("Invalid value entered. Please enter a new value.\n");
			}
		}

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
	head->data = (char)(rand() % 26 + 97);//generates a random lower case letter from using the ascii table
	head->next = NULL;

	for(int i = 0; i < amountOfNodes - 1; ++i)
	{
		tail->next = (ptr)malloc(sizeof(_p));
		tail = tail->next;
		tail->next = NULL;
		tail->data = (char)(rand() % 26 + 97);//generates a random lower case letter from using the ascii table
	}
	return head;
}




void PrintList(const ptr head)
{
	int counter = 1;

	ptr temp = head;
	printf("Data of %d: %c\n", counter, temp->data);

	while(temp->next != NULL)
	{
		++counter;
		temp = temp->next;
		printf("Data of %d: %c\n", counter, temp->data);
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
			//allocate 1 node at end of list for new character
			tail->next = (ptr)malloc(sizeof(_p));
			tail = tail->next;
			tail->next = NULL;
			//remember that tail does not point to the end of the list, but it's ok because tail doesn't get used again in this function and will be destroyed upon leaving function
			temp = AddBegin(head);
			break;
		case 2:
			//allocate 1 node at end of list for new character
			tail->next = (ptr)malloc(sizeof(_p));
			tail = tail->next;
			tail->next = NULL;
			temp = AddEnd(head);
			break;
		case 3:
			//allocate 1 node at end of list for new character
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
	char userInput;

	printf("What letter would you like to add?\n");
	fflush(stdin);
	scanf("%c", &userInput);

	//add user's character to front of new list
	tail2 = head2 = (ptr)malloc(sizeof(_p));
	tail2->data = userInput;
	tail2->next = NULL;

	ptr temp = head;

	while(temp->next != NULL)
	{
		tail2->next = (ptr)malloc(sizeof(_p));
		tail2 = tail2->next;
		tail2->next = NULL;
		tail2->data = temp->data;
		temp = temp->next;
	}
	return head2;
}




ptr AddEnd(const ptr head)
{
	ptr temp = head;
	char userInput;

	temp = Search(temp, -1);
	
	printf("What letter would you like to add?\n");
	fflush(stdin);
	scanf("%c", &userInput);
	
	temp->data = userInput;

	return head;
}




ptr AddN(const ptr head)
{
	ptr temp = head;
	ptr head2;
	ptr tail2;
	char userInput;
	int userPos = 0;
	int listLength = 0;
	int counter = 1;

	listLength = Length(temp);

	//determine what character user would like to insert
	printf("What letter would you like to add?\n");
	fflush(stdin);
	scanf("%c", &userInput);

	//determine position to place user's character into
	while(userPos <= 0)
	{
		printf("At what position would you like to add a %c to the list?\n", userInput);
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
		else
		{
			printf("%c will be added after position %d.\n", userInput, userPos);
		}
	}

	tail2 = head2 = (ptr)malloc(sizeof(_p));
	tail2->data = temp->data;
	tail2->next = NULL;
	temp = temp->next;
	
	while(counter < userPos)
	{
		tail2->next = (ptr)malloc(sizeof(_p));
		tail2 = tail2->next;
		tail2->next = NULL;
		tail2->data = temp->data;
		temp = temp->next;
		++counter;
	}

	tail2->next = (ptr)malloc(sizeof(_p));
	tail2 = tail2->next;
	tail2->next = NULL;
	tail2->data = userInput;

	while(counter < listLength-1)//-1 because an extra node was allocated premptively on purpose
	{
		tail2->next = (ptr)malloc(sizeof(_p));
		tail2 = tail2->next;
		tail2->next = NULL;
		tail2->data = temp->data;
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
		tail2->data = temp->data;
		tail2->next = NULL;

		while(temp->next != NULL)
		{
			temp = temp->next;
			tail2->next = (ptr)malloc(sizeof(_p));
			tail2 = tail2->next;
			tail2->data = temp->data;
			tail2->next = NULL;
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

	//determine position to remove character from
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
			printf("To remove the first element please use the remove first character function provided in the previous list of choices.\n");
		}
		else
		{
			printf("A character will be removed after at position %d.\n", userPos);
		}
	}

	tail2 = head2 = (ptr)malloc(sizeof(_p));
	tail2->data = temp->data;
	tail2->next = NULL;
	
	while(counter < userPos)
	{
		temp = temp->next;
		tail2->next = (ptr)malloc(sizeof(_p));
		tail2 = tail2->next;
		tail2->next = NULL;
		tail2->data = temp->data;
		++counter;
	}
	temp = temp->next;

	while(counter < listLength-1)//-1 because one node of temp has been skipped on purpose
	{
		temp = temp->next;
		tail2->next = (ptr)malloc(sizeof(_p));
		tail2 = tail2->next;
		tail2->next = NULL;
		tail2->data = temp->data;
		++counter;
	}

	return head2;
}
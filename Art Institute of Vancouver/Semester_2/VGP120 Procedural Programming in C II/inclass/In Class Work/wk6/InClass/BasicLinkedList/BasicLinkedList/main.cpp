#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct listNode
{
	int data;
	struct listNode *nextPtr;
};

void insert( struct listNode* );
void printList( struct listNode* );

int main()
{
	int choice;
	int nodeCount = 0;

	srand ( time(NULL) );

	struct listNode* const headPtr = ( struct listNode* )malloc ( sizeof(struct listNode) );
	//headPtr = ( struct listNode* )malloc ( sizeof(struct listNode) );
	++nodeCount;
	headPtr->nextPtr = NULL;
	headPtr->data = rand() % 100 + 1;

	struct listNode* tempPtr = headPtr;

	printf( "1: Insert\n" );
	printf( "0: Quit\n" );
	scanf( "%d", &choice );

	while( choice != 0 )
	{
		insert( tempPtr );

		printf( "1: Insert\n" );
		printf( "0: Quit\n" );
		scanf( "%d", &choice );
	}
	
	printList( tempPtr );

	return 0;
}

void insert( struct listNode* tempPtr )
{
	struct listNode* newNodePtr;
	newNodePtr = ( struct listNode* )malloc ( sizeof(struct listNode) );
	newNodePtr->data = rand() % 100 + 1;
	newNodePtr->nextPtr = NULL;

	// check if at last node
	while ( tempPtr->nextPtr != NULL )
	{
		tempPtr = tempPtr->nextPtr;	
	}

	tempPtr->nextPtr = newNodePtr;

}

void printList( struct listNode* currentPtr )
{
	int tabCounter = 0;

	// if list is empty
	if( currentPtr == NULL )
	{
		printf( "List is empty.\n" );
	}
	else
	{
		printf( "The list is:\n" );
		//while not at end of list
		while( currentPtr != NULL )
		{
			if( tabCounter == 4 )
			{
				printf( "%d\n", currentPtr->data );
				currentPtr = currentPtr->nextPtr;
				tabCounter = 0;
			}
			else
			{
				printf( "%d\t", currentPtr->data );
				currentPtr = currentPtr->nextPtr;
				++tabCounter;
			}
		}
	}

	printf("\n");
}
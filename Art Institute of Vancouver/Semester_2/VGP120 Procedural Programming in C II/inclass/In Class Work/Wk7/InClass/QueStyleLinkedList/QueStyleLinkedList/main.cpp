#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct queue
{
	int someRandomData;
	struct queue* nextPtr;
	struct queue* prevPtr;
};

void Insert( struct queue*&, struct queue*& );
void Remove( struct queue*&, struct queue*& );
void Print( struct queue*, struct queue* );

int main()
{
	srand( (unsigned int)time(NULL) );

	struct queue* frontPtr = NULL;
	struct queue* rearPtr = NULL;
	int choice = -1;

	while( choice != 0 )
	{
		printf( "What would you like to do?\n");
		printf( "1: Insert into the rear of the list.\n" );
		printf( "2: Remove from the front of the list.\n") ;
		printf( "3: Print list.\n") ;
		printf( "0: Quit.\n") ;
		scanf( "%d", &choice );

		switch ( choice )
		{
			//quit
			case 0:
			break;

			case 1:
				Insert( frontPtr, rearPtr );
				printf("\n");
			break;
			
			case 2:
				Remove( frontPtr, rearPtr );
				printf("\n");
			break;

			case 3:
				Print( frontPtr, rearPtr );
				printf("\n");
			break;

			default:
				printf( "Invalid choice.\n\n" );
			break;

		}//end switch	

	}

	return 0;
}

void Insert( struct queue*& frontPtr, struct queue*& rearPtr )
{
	//if queue empty
	if( (frontPtr == rearPtr) && (frontPtr == NULL))
	{
		struct queue* newNodePtr = ( struct queue* )malloc ( sizeof(struct queue) );
		newNodePtr->nextPtr = NULL;
		newNodePtr->prevPtr = NULL;
		newNodePtr->someRandomData = rand() % 101;
		frontPtr = newNodePtr;
		rearPtr = newNodePtr;
		rearPtr->nextPtr = NULL;
	}
	else
	{
		struct queue* newNodePtr = ( struct queue* )malloc ( sizeof(struct queue) );
		newNodePtr->someRandomData = rand() % 101;
		rearPtr->nextPtr = newNodePtr;
		newNodePtr->prevPtr = rearPtr;
		rearPtr = newNodePtr;
		rearPtr->nextPtr = NULL;
	}

}


void Remove( struct queue*& frontPtr, struct queue*& rearPtr )
{
	struct queue* tempPtr = frontPtr;
	frontPtr = frontPtr->nextPtr;

	free( tempPtr );
	tempPtr = NULL;
}


void Print( struct queue* frontPtr, struct queue* rearPtr )
{
	while( frontPtr->nextPtr != NULL )
	{
		printf( "%d\n", frontPtr->someRandomData );
		frontPtr = frontPtr->nextPtr;
	}
}


/* NEXT TRY THIS!! =)

BEFORE:

| Data: 23		|			| Data: 4		|
|				|	--->	|				|
| Priority: 5	|			| Priority: 3	|

AFTER:

| Data: 23		|			| Data: 4		|
|				|	////	|				|
| Priority: 5	|			| Priority: 3	|
		|							^
		|							|
		------->| Data: 117		|---
				|				|
				| Priority: 4	|

*/
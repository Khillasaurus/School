#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct card
{
	int face;	// 1: spades, 2: hearts, 3: clubs, 4: diamonds
	int number;	// 1: ace, 11: jack, 12: queen, 13: king
	struct card *nextPtr;
};

//function prototypes
void fillDeck( struct card* );
void printStates( int*, int*, int*, struct card*, struct card*, struct card*); // testing function!
void pickup( struct card*, struct card*, int*, int* );

int main()
{
	srand ( time(NULL) );

	// ---- INITIALIZE VARIABLES AND SET NECCESARY STARTING VALUES ----

	int deckArray[52];
	int* deckArrayPtr = deckArray;
	for( int i = 0; i < 52; ++i )
	{
		deckArray[i] = 1;
	}

	int hand1Array[52];
	int* hand1ArrayPtr = hand1Array;
	for( int i = 0; i < 52; ++i )
	{
		hand1Array[i] = 0;
	}
	
	int hand2Array[52];
	int* hand2ArrayPtr = hand2Array;
	for( int i = 0; i < 52; ++i )
	{
		hand2Array[i] = 0;
	}

	//struct card* const deckHeadPtr = ( struct card* )malloc ( sizeof(struct card) );
	//deckHeadPtr->nextPtr = NULL;
	struct card* deckStartPtr = NULL;
	//Create pointer that points to the same thing as deckHeadPtr but isn't constant.
	//This prevents any attempt to tamper with the beginning of the deck list.
	//struct card* deckStartPtr = deckHeadPtr;

	//struct card* const hand1HeadPtr = ( struct card* )malloc ( sizeof(struct card) );
	//hand1HeadPtr->nextPtr = NULL;
	struct card* hand1StartPtr = NULL;
	//same reasoning applies here as with deckStartPtr
	//struct card* hand1StartPtr = hand1HeadPtr;
	
	//struct card* const hand2HeadPtr = ( struct card* )malloc ( sizeof(struct card) );
	//hand2HeadPtr->nextPtr = NULL;
	struct card* hand2StartPtr = NULL;
	//same reasoning applies here as with deckStartPtr
	//struct card* hand2StartPtr = hand2HeadPtr;

	//-----------------------------------------------------------------------------------

	// testing function!
	printStates( deckArrayPtr, hand1ArrayPtr, hand2ArrayPtr, deckStartPtr, hand1StartPtr, hand2StartPtr );

	// creates a deck of 52 cards
	fillDeck( deckStartPtr );

	// testing function!
	printStates( deckArrayPtr, hand1ArrayPtr, hand2ArrayPtr, deckStartPtr, hand1StartPtr, hand2StartPtr );

	// each player "picks up" twice as this is the equivalent of dealing a hand
	pickup( deckStartPtr, hand1StartPtr, deckArrayPtr, hand1ArrayPtr );
	pickup( deckStartPtr, hand1StartPtr, deckArrayPtr, hand1ArrayPtr );
	pickup( deckStartPtr, hand2StartPtr, deckArrayPtr, hand2ArrayPtr );
	pickup( deckStartPtr, hand2StartPtr, deckArrayPtr, hand2ArrayPtr );

	return 0;
}//end main()


void fillDeck( struct card* deckStartPtr )
{
	// variable required to account for deckHeadPtr already existing
	//int startingPoint = 1;

	// define 1st card
	//deckStartPtr->face = 1;
	//deckStartPtr->number = 1;

	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 13; ++j )
		{
			struct card* newNodePtr;
			newNodePtr = ( struct card* )malloc ( sizeof(struct card) );
			newNodePtr->face = ( i+1 );
			newNodePtr->number = ( j+1 );
			newNodePtr->nextPtr = NULL;

			// check if at last node
			if ( deckStartPtr->nextPtr != NULL )
			{
				deckStartPtr = deckStartPtr->nextPtr;
			}
			deckStartPtr->nextPtr = newNodePtr;
			//startingPoint = 0;
		}
	}
}//end fillDeck()


void printStates( int* deckArrayPtr, int* hand1ArrayPtr, int* hand2ArrayPtr, struct card* deckStartPtr, struct card* hand1StartPtr, struct card* hand2StartPtr )
{
	// ---- PRINT DECK STATE ----

	for( int i = 0; i < 52; ++i )
	{
		if( ((i+1)%13) == 0 )
		{
			printf("%d\n", deckArrayPtr[i]);
		}
		else
		{
			printf("%d ", deckArrayPtr[i]);
		}
	}
	
	// if list is empty
	if( deckStartPtr == NULL )
	{
		printf( "List is empty.\n" );
	}
	else
	{
		printf( "The list is:\n" );
		//while not at end of list
		while( deckStartPtr != NULL )
		{
			printf( "Face: %d\t", deckStartPtr->face );
			printf( "Number: %d\n", deckStartPtr->number );
			deckStartPtr = deckStartPtr->nextPtr;
		}
	}
	printf("\n");

	// ---- PRINT HAND1 STATE ----

	for( int i = 0; i < 52; ++i )
	{
		if( ((i+1)%13) == 0 )
		{
			printf("%d\n", hand1ArrayPtr[i]);
		}
		else
		{
			printf("%d ", hand1ArrayPtr[i]);
		}
	}

	// if list is empty
	if( hand1StartPtr == NULL )
	{
		printf( "Hand1 List is empty.\n" );
	}
	else
	{
		printf( "The Hand1 list is:\n" );
		//while not at end of list
		while( hand1StartPtr != NULL )
		{
			printf( "Face: %d\t", hand1StartPtr->face );
			printf( "Number: %d\n", hand1StartPtr->number );
			hand1StartPtr = hand1StartPtr->nextPtr;
		}
	}
	printf("\n");
	
	// ---- PRINT HAND2 STATE ----

	for( int i = 0; i < 52; ++i )
	{
		if( ((i+1)%13) == 0 )
		{
			printf("%d\n", hand2ArrayPtr[i]);
		}
		else
		{
			printf("%d ", hand2ArrayPtr[i]);
		}
	}

	// if list is empty
	if( hand2StartPtr == NULL )
	{
		printf( "Hand2 List is empty.\n" );
	}
	else
	{
		printf( "The Hand2 list is:\n" );
		//while not at end of list
		while( hand2StartPtr != NULL )
		{
			printf( "Face: %d\t", hand2StartPtr->face );
			printf( "Number: %d\n", hand2StartPtr->number );
			hand2StartPtr = hand2StartPtr->nextPtr;
		}
	}
	printf("\n");

}//end printState

void pickup( struct card* sPtr, struct card* handStartPtr, int* removingLocation, int* addingLocation )
{
	struct card* previousPtr;
	struct card* currentPtr;
	struct card* tempPtr;
	int cardNumber = rand() % 51;
	int faceNumber = 0;
	bool firstNode = true;

	//copy of tempPtr used in order to delete node from deck list and add to hand list
	struct card* copyPtr = ( struct card* )malloc ( sizeof(struct card) );
	copyPtr->nextPtr = NULL;

	removingLocation[cardNumber] = 0;
	addingLocation[cardNumber] = 1;
	
	while( cardNumber > 13 )
	{
		cardNumber -= 13;
		++faceNumber;
	}

	// ---- REMOVE CARD NODE FROM DECK LIST ----
	// if first node
	if( sPtr->face == faceNumber && sPtr->number == cardNumber )
	{
		tempPtr = sPtr;
		sPtr = sPtr->nextPtr;
		copyPtr->face = tempPtr->face;
		copyPtr->number = tempPtr->number;
		free( tempPtr );
	}
	else
	{
		previousPtr = sPtr;
		currentPtr = sPtr->nextPtr;

		//search for card in deck
		while( currentPtr != NULL )
		{
			if( (currentPtr->face != faceNumber) || (currentPtr->number != cardNumber) )
			{
				previousPtr = currentPtr;
				currentPtr = currentPtr->nextPtr;
				copyPtr->face = currentPtr->face;
				copyPtr->number = currentPtr->number;
			}
			else 
			{
				break;
			}
		}

		if( currentPtr != NULL )
		{
			tempPtr = currentPtr;
			previousPtr->nextPtr = currentPtr->nextPtr;
			free( tempPtr );
		}
	}

	// ---- ADD CARD NODE TO HAND LIST ----
	//while not at end of list
	while( handStartPtr != NULL )
	{
		//move forward to next node
		handStartPtr = handStartPtr->nextPtr;
	}
	if( firstNode == false )
	{
		struct card* newNodePtr;
		newNodePtr = ( struct card* )malloc ( sizeof(struct card) );
		handStartPtr->face = copyPtr->face;
		handStartPtr->number = copyPtr->number;
		handStartPtr->nextPtr = newNodePtr;
	}
	else
	{
		handStartPtr->face = copyPtr->face;
		handStartPtr->number = copyPtr->number;
		firstNode = true;
	}
}//end pickup()
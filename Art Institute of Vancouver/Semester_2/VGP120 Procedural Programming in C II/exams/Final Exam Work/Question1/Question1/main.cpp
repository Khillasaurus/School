#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct queue
{
	int someRandomData;
	struct queue* nextPtr;
	struct queue* prevPtr;
};

void Insert( struct queue*&, struct queue*&, char [30][30] );
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


		char word[30][30]; // array of 30 words that can be up to 30 characters in length
		int lineNumber = 0;

		FILE *cfPtr; //cfPtr = words.txt file pointer

		// fopen opens file; exits program if file cannot be opened
		if( (cfPtr = fopen("words.txt", "r")) == NULL )
		{
			printf("File could not be opened\n" );
		}
		else // read word from file
		{
			//while not end of file
			while( !feof(cfPtr) )
			{
				int counter = 0;
				word[counter][] = fscanf( cfPtr, "%s", word );
				++cfPtr;
				++counter;
			}
		}
	
		//sort words
		char wordHold[30];
		for( int i = 0; i < 30; ++i )
		{
			for( int j = i; j < 30; ++j )
			{
				if( word[i] < word[j] )
				{
					wordHold = word[i][];
					word[i][] = word[j][];
					word[j][] = wordHold;
				}
			}
		}


		switch ( choice )
		{
			//quit
			case 0:
			break;

			case 1:
				Insert( frontPtr, rearPtr, word[30][30] );
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

		fclose( cfPtr ); //fclose closes the file

	}

	return 0;
}

void Insert( struct queue*& frontPtr, struct queue*& rearPtr, char word[30][30] )
{
	//if queue empty
	if( (frontPtr == rearPtr) && (frontPtr == NULL))
	{
		struct queue* newNodePtr = ( struct queue* )malloc ( sizeof(struct queue) );
		newNodePtr->nextPtr = NULL;
		newNodePtr->prevPtr = NULL;
		newNodePtr->someRandomData = word[0][];
		frontPtr = newNodePtr;
		rearPtr = newNodePtr;
		rearPtr->nextPtr = NULL;
	}
	else
	{
		for( int i = 1; i < 30; ++i )
		{
			struct queue* newNodePtr = ( struct queue* )malloc ( sizeof(struct queue) );
			newNodePtr->someRandomData = word[i][];
			rearPtr->nextPtr = newNodePtr;
			newNodePtr->prevPtr = rearPtr;
			rearPtr = newNodePtr;
			rearPtr->nextPtr = NULL;
		}
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

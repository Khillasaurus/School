#include <stdio.h>
#include <stdlib.h>

struct prices
{
	float price;
	int quantity;
};

struct stackNode
{
	int ID;
	float data;
	struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

//function prototypes
void push( StackNodePtr *topPtr, int ID, float info );
int pop( StackNodePtr *topPtr );
int isEmpty( StackNodePtr topPtr );
void printStack( StackNodePtr currentPtr );

int main( void )
{
	FILE *cfPtr; /* prices.txt file pointer */
	struct prices priceA = {0.00, 0};
	FILE *cfPtrB; /* prices.txt file pointer */
	StackNode B = { 0, 0.00 };

	StackNodePtr stackPtr = NULL; /* points to stack top */
	float value;
	int count = 0;

	//read data from file
	//push value onto stack
			if( ( cfPtr = fopen( "prices.txt", "rb" ) ) == NULL )
			{
				printf( "File could not be opened.\n" );
			}
			else
			{ 
			//input from file
				while( !feof( cfPtr ) )
				{ 
					++count;
					fread( &priceA, sizeof( struct prices ), 1, cfPtr );
					value = priceA.price * priceA.quantity;
					push( &stackPtr, count, value );
				}
				count = 0;
			}
			fclose( cfPtr ); /* fclose closes the file */


			float dataA;
			float dataB;
			//put data from stack into sorted stack from highest to lowest
			if( ( cfPtr = fopen( "prices.txt", "rb" ) ) == NULL )
			{
				printf( "File could not be opened.\n" );
			}
			else
			{
				fread( &priceA, sizeof( struct B ), 1, cfPtr );
				dataA = B.data;
				int count = 0;
				while( !feof( cfPtr ) )
				{
					++count;
					fread( &priceA, sizeof( struct B ), 1, cfPtr );
					dataB = B.data;
					if(dataA > dataB)
					{
						push(B, count, dataA);
					}
				}
				count = 0;
			}
			
			
		printStack( B );

   return 0;

}


/* Insert a node at the stack top */
void push( StackNodePtr *topPtr, int ID, float info )
{ 
   StackNodePtr newPtr; /* pointer to new node */

   newPtr = malloc( sizeof( StackNode ) );

   /* insert the node at stack top */
   if ( newPtr != NULL ) {   
      newPtr->data = info;
	  newPtr->ID = ID;
      newPtr->nextPtr = *topPtr;
      *topPtr = newPtr;
   }
   else
   { /* no space available */
      printf( "%d not inserted. No memory available.\n", info );
   }

}

/* Remove a node from the stack top */
int pop( StackNodePtr *topPtr )
{ 
   StackNodePtr tempPtr; /* temporary node pointer */
   int popValue; /* node value */

   tempPtr = *topPtr;
   popValue = ( *topPtr )->data;
   *topPtr = ( *topPtr )->nextPtr;
   free( tempPtr );

   return popValue;

}

/* Print the stack */
void printStack( StackNodePtr currentPtr )
{ 

   /* if stack is empty */
   if ( currentPtr == NULL ) {
      printf( "The stack is empty.\n\n" );
   }
   else { 
      printf( "The stack is:\n" );

      /* while not the end of the stack */
      while ( currentPtr != NULL ) { 
         printf( "%.2f --> ", currentPtr->data );
         currentPtr = currentPtr->nextPtr;
      }

      printf( "NULL\n\n" );
   }

}

/* Return 1 if the stack is empty, 0 otherwise */
int isEmpty( StackNodePtr topPtr )
{ 
   return topPtr == NULL;

}
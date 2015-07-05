//-----------------------------
// Created by: Daniel Schenker
// Created On: January 10, 2012
// Copyright: Daniel Schenker
//-----------------------------

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//function prototypes
void FillStringWithUserInput(char *&);

int main( void )
{ 
	char stringA[50];
	char stringB[50];
	char stringC[50];
	char* stringAPtr = stringA;
	char* stringBPtr = stringB;
	char* stringCPtr = stringC;

	FillStringWithUserInput( stringAPtr );
	FillStringWithUserInput( stringBPtr );
	FillStringWithUserInput( stringCPtr );

	//print strings alphabetically

	//A before B
	if( strcmp(stringAPtr, stringBPtr) < 0 )
	{
		//A before C before B
		if( strcmp(stringAPtr, stringCPtr) < 0 )
		{
			printf( "%s\n", *stringAPtr );

			//A before B before C
			if( strcmp(stringBPtr, stringCPtr) < 0 )
			{
				printf( "%s\n", *stringBPtr );
				printf( "%s\n", *stringCPtr );
			}
			//A before C before B
			else
			{
				printf( "%s\n", *stringCPtr );
				printf( "%s\n", *stringBPtr );
			}
		}
		//C before A before B
		else 
		{
			printf( "%s\n", *stringCPtr );
			printf( "%s\n", *stringAPtr );
			printf( "%s\n", *stringBPtr );
		}
	}
	//B before C
	else if( strcmp(stringBPtr, stringCPtr) < 0 )
	{
		printf( "%s\n", *stringBPtr );

		//B before A before C
		if( strcmp(stringAPtr, stringCPtr) < 0 )
		{
			printf( "%s\n", *stringAPtr );
			printf( "%s\n", *stringCPtr );
		}
		//B before C before A
		else
		{
			printf( "%s\n", *stringCPtr );
			printf( "%s\n", *stringAPtr );
		}
	}
	//C before B before A
	else
	{
		printf( "%s\n", *stringCPtr );
		printf( "%s\n", *stringBPtr );
		printf( "%s\n", *stringAPtr );
	}

	printf( "\n" );

	return 0; //indicates successful termination

} //end main

void FillStringWithUserInput( char *&temp )
{
	printf( "Please enter sentence.\n" );
	gets( temp );
	printf( "\n" );
	
	return;
}
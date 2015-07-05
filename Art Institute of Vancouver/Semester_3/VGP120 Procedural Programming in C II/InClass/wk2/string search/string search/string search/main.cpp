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
void FillStringWithUserInput( char*&, int );
void StringSearch( char*, char* );


//global variables
enum state
{
	SENTENCE,
	WORD
};


int main( void )
{ 
	char stringA[50];
	char stringSearch[50];
	char* stringAPtr = stringA;
	char* stringSearchPtr = stringSearch;

	FillStringWithUserInput( stringAPtr, SENTENCE );
	FillStringWithUserInput( stringSearchPtr, WORD );

	StringSearch( stringAPtr, stringSearchPtr );

	
	return 0; //indicates successful termination

} //end main


void FillStringWithUserInput( char* &temp, int state )
{

	switch( state )
	{
		case SENTENCE:
			{
				printf( "Please enter a sentence.\n" );
				gets( temp );
				break;
			}
		case WORD:
			{
				printf( "Please enter the word you would like to search for.\n" );
				scanf( "%s", temp );
				break;
			}
		default:
			{
				printf( "\nERROR: INVALID STATE\n\n" );
				exit(1);
			}
	}

	printf( "\n" );
	
	return;
}


void StringSearch( char* sentence, char* word )
{
	char *hold = sentence;

	for( int charCount = 0; *sentence != '\0'; ++charCount )
	{
		//strstr( sentence, word ); //finds first occurence so this won't work, but I intend to use this
		++sentence;
	}
}
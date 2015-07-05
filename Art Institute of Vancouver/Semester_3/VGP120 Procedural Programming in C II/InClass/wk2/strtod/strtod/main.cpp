//-----------------------------
// Created by: Daniel Schenker
// Created On: January 10, 2012
// Copyright: Daniel Schenker
//-----------------------------

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main( void )
{ 
	//initialize string pointer
	char *string = "There are 51.2% admitted"; //initialize string

	double d;//variable to hold converted sequence
	char *stringPtr = string;

	printf( "The string \"%s\" is converted to:\n", string );

	printf( "String Before:\t" );
	while( !(isdigit(*stringPtr)) )
	{
		printf( "%c", *stringPtr );
		++stringPtr;
	}
	printf( "\n" );

	d = strtod( stringPtr, &stringPtr );
	printf( "Double Value:\t%.2f\n", d );
	printf( "String After:\t%s\n", stringPtr );

	return 0; //indicates successful termination

} //end main

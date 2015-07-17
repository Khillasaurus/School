//========================================================================================================================================================================
// Filename:	main.cpp
// Created by:	Daniel Schenker
// Description: Driver program for MathLib
//========================================================================================================================================================================

//========================================================================================================================================================================
// Includes
//========================================================================================================================================================================
#include <stdio.h>
#include <stdlib.h>

#include "../MathLib/Vector2.h"


//========================================================================================================================================================================
// Prototypes
//========================================================================================================================================================================

int instructions();
Vector2 getVector();
void printVector(Vector2);

//========================================================================================================================================================================
// Main
//========================================================================================================================================================================
void main()
{
	Vector2 a;
	Vector2 b;
	Vector2 final;
	int choice = 0;
	float scale = 0;
	float rotate = 0;

	choice = instructions();

	while ( choice != 0 )
	{ 
		switch ( choice )
		{
			//magnitude
			case 1:
				a = getVector();
				printf( "Magnitude: %f\n\n", Magnitude(a) );
			break;

			//normalize
			case 2:
				a = getVector();
				final = Normalize( a );
				printf("Normalized: ");
				printVector( final );
			break;

			//invert
			case 3:
				a = getVector();
				final = Invert( a );
				printf("Inverted: ");
				printVector( final );
			break;

			//perpendicular
			case 4:
				a = getVector();
				b = getVector();
				printf("Perpendicular: %f\n\n", Perpendicular(a, b) );
			break;

			//add
			case 5:
				a = getVector();
				b = getVector();
				final = Add( a, b );
				printf("Added: ");
				printVector( final );
			break;

			//subtract
			case 6:
				a = getVector();
				b = getVector();
				final = Sub( a, b );
				printf("Subtracted: ");
				printVector( final );
			break;

			//scale
			case 7:
				a = getVector();
				printf("What would you like to scale this vector by?\t\n");
				scanf("%f", &scale);
				final = Scale( a, scale );
				printf("Scaled: ");
				printVector( final );
			break;

			//rotate
			case 8:
				a = getVector();
				printf("How many rad would you like to rotate by?\n");
				scanf("%f", &rotate);
				//ensure 2D vector for rotation
				a.z = 0;
				printf("A 2D rotation will occur around the origin.\n");
				final = Rotate( a, rotate );
				printVector( final );
			break;

			//dot
			case 9:
				a = getVector();
				b = getVector();
				printf("%f\n\n", Dot(a, b) );
			break;

			case 0:
			break;

			default:
				printf( "Invalid choice.\n\n" );
			break;

		}//end switch	
		choice = instructions();
	}//end while

	// insert test code here
	// remember using left handed coordinate system is easier

	system( "PAUSE" );
}

int instructions()
{
	int choice;

	printf( "Which operation would you like to perform?\n" );
	printf( "1: Return Vector Magnitude\n" );
	printf( "2: Normalize\n" );
	printf( "3: Invert Vector\n" );
	printf( "4: Return Cross Product\n" );
	printf( "5: Add\n" );
	printf( "6: Subtract\n" );
	printf( "7: Scale\n" );
	printf( "8: Rotate\n" );
	printf( "9: Return Dot Product\n" );
	printf( "0: Quit\n" );
	
	scanf( "%d", &choice );

	return choice;
}

Vector2 getVector()
{
	Vector2 aVector;

	printf("Enter vector specifications:\n");
	printf("x: ");
	scanf("%f", &aVector.x);
	printf("y: ");
	scanf("%f", &aVector.y);
	printf("z: ");
	scanf("%f", &aVector.z);

	return aVector;
}

void printVector(Vector2 aVector)
{
	printf("Result:\n");
	printf("Vector: %f, %f, %f\n\n", aVector.x, aVector.y, aVector.z );
}
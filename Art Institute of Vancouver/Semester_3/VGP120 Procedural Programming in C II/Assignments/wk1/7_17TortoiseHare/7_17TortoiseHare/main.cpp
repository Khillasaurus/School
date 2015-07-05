#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//function prototypes
int CalculateMove( bool );
int MovePosition( int, int );
void PrintState( char [], const int, int, int );
void FillTrack( char [], const int );

int main()
{

	const int kStart = 1;
	const int kFinish = 70;
	int tortoisePosition = kStart;
	int harePosition = kStart;
	bool isTortoise = true;
	unsigned int clock = 0;
	const int kSize = 83;
	char track[kSize];

	/*
	Animal		Move Type		Percentage of the Time		Actual Move
	---------------------------------------------------------------------
	Tortoise	Fast plod				50%				3 squares to the right
				Slip					20%				6 squares to the left
				Slow plod				30%				1 square to the right

	Hare		Sleep					20%				No move at all
				Big hop					20%				9 squares to the right
				Big slip				10%				12 squares to the left
				Small hop				30%				1 square to the right
				Small slip				20%				2 squares to the left
	*/

	//initialize random seed
	srand( (unsigned)time(NULL) );

	while( tortoisePosition < kFinish && harePosition < kFinish )
	{
		isTortoise = true;
		tortoisePosition = MovePosition( CalculateMove(isTortoise), tortoisePosition );
		isTortoise = false;
		harePosition = MovePosition( CalculateMove(isTortoise), harePosition );
		PrintState( track, kSize, tortoisePosition, harePosition );
	}

	if( tortoisePosition >= kFinish && harePosition < kFinish )
	{
		printf( "TORTOISE WINS!!! YAY!!!\n" );
	}
	else if( harePosition >= kFinish && tortoisePosition < kFinish )
	{
		printf( "Hare wins. Yuch.\n" );
	}
	else
	{
		printf( "It's a tie.\n" );
	}

}

int CalculateMove( bool isTortoise )
{
	int moveType = 0;
	int moveSpaces = 0;
	
	moveType = rand() % 10 + 1;

	if( isTortoise )
	{
		if( moveType <= 5 )
		{
			moveSpaces = 3;
		}
		else if( moveType <= 7 )
		{
			moveSpaces = -6;
		}
		else
		{
			moveSpaces = 1;
		}
	}
	else
	{
		if( moveType <= 2 )
		{
			moveSpaces = 0;
		}
		else if( moveType <= 4 )
		{
			moveSpaces = 9;
		}
		else if( moveType <= 5 )
		{
			moveSpaces = -12;
		}
		else if( moveType <= 8 )
		{
			moveSpaces = 1;
		}
		else
		{
			moveSpaces = -2;
		}
	}


	return moveSpaces;
}

int MovePosition( int moveSpaces, int position )
{
	if( position + moveSpaces < 0 )
	{
		return 0;
	}
	else
	{
		return ( position + moveSpaces );
	}
}

void PrintState( char track[], const int kSize, int tortoisePosition, int harePosition )
{
	//change blank spaces in track to racer positions, and change previous racer positions to blank spaces
	for( int i = 0; i < kSize; ++i )
	{
		if( i == tortoisePosition && i == harePosition )
		{
			printf( "OUCH!!!\n" );
			track[i] = 'O';
		}
		else if( i == tortoisePosition && i != harePosition )
		{
			track[i] = 'T';
		}
		else if( i != tortoisePosition && i == harePosition )
		{
			track[i] = 'H';
		}
		else
		{
			track[i] = ' ';
		}

		printf( "%c", track[i] );
	}
	printf( "\n" );


}

void FillTrack( char track[], const int kSize )
{
	for( int i = 0; i < kSize; ++i )
	{
	 track[i] = ' ';
	}
}
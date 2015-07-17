#include <stdio.h>

void PrintEdge( int [4][4] );
void PrintNodeDegree( int [4][4] );
void Traverse();

int main()
{
	printf( "There are 4 cities. City  0, 1, 2, and 3.\n\n" );

	int cities [4][4] = {0};

	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			if( i == j )
			{
				cities[i][j] = 0;
			}
			else
			{
				printf( "How far from city %d to city %d?\n", i, j );
				printf( "If there is no connection between the two cities enter -1.\n" );
				scanf( "%d", &cities[i][j] );
			}
		}
	}

	int choice = -1;
	while( choice != 0 )
	{
		printf( "What would you like to do?\n" );
		printf( "1: PrintEdge.\n" );
		printf( "2: PrintNodeDegree.\n" );
		printf( "0: Quit.\n" );
		scanf( "%d", &choice  );

		if( choice == 1 )
		{
			PrintEdge( cities );
			printf( "\n" );
		}
		else if( choice == 2 )
		{
			PrintNodeDegree( cities );
			printf( "\n" );
		}
	}

	return 0;
}

void PrintEdge( int cities [4][4] )
{
	int city1 = 0;
	int city2 = 0;
	printf( "Enter the city number 1.\n" );
	scanf( "%d", &city1 );
	printf( "Enter the city number 2.\n" );
	scanf( "%d", &city1 );
	printf( "The distance from city %d to city %d is: %d.\n", city1, city2, cities[city1][city2] );
}

void PrintNodeDegree( int cities [4][4] )
{
	int city = -1;
	int counter = 0;

	printf( "For which city would you like to find out it's degree?\n" );
	scanf( "%d", &city );

	for( int i = 0; i < 4; ++i )
	{
		if( cities[city][i] > 0 )
		{
		++counter;
		}
	}
	
	printf( "City %d is degree %d.\n", city, counter );

}

void Traverse()
{
	int city1 = 0;
	int city2 = 0;
}
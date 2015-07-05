#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void push( int [] );
int pop( int [] );
int isEmpty();

int g_top;
const int g_size = 20;

int main()
{
	int choice = 0;

	int list[g_size] = {0};

	g_top = 0;

	printf( "Would you like to push, pop or quit? 1, 2 or 3 respectively.\n" );
	scanf( "%d", &choice );

	while( choice != 0 )
	{
		if( choice == 1 )
		{
			push( list );
		}
		else if( choice == 2 )
		{
			printf("%d\n", pop(list) );
		}
		else
		{
			break;
		}
		printf( "Would you like to push or pop? 1 or 2 respectively.\n" );
		scanf( "%d", &choice );
	}
}

void push( int &list[] )
{
	int input = 0;

	while( input < 1 )
	{
		printf( "What integer greater than one would you like to add to the stack?\n" );
		scanf("%d", &input);
	}
	if( g_top < (g_size - 1) )
	{
		list[g_top] = input;
		++g_top;
	}

}

int pop( int &list[] )
{
	return list[g_top];
}

int isEmpty()
{
	return ;
}
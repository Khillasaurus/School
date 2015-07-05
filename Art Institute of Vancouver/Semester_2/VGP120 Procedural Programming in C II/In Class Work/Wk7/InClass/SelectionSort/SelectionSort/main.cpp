//NOT FINISHED!!!

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FillList( int*, const int );
void PrintList( int*, int );
int* FindSmallest( int*, const int );
void Swap( int*, int* );

int main()
{
	const int size = 5;
	int list[size];
	const int* listPtr = list;
	int* tempPtr = list;
	int* currentPtr = list;
	int* smallestCorrectPtr = list;

	srand( (unsigned int)time(NULL) );

	FillList( tempPtr, size );
	currentPtr = FindSmallest( currentPtr, size );
	
	//if not at last element
	if( *currentPtr != list[size] )
	{
		Swap( currentPtr, smallestCorrectPtr );
	}


	return 0;
}

void FillList( int* tempPtr, const int size )
{
	for( int i = 0; i < size; ++i )
	{
		tempPtr[i] = rand() % 101;
	}
}

void PrintList( int* tempPtr, const int size)
{
	for( int i = 0; i < size; ++i )
	{
		printf( "%d\n", tempPtr[i] );
	}

}

int* FindSmallest( int* currentPtr, const int size )
{
	for( int i = 0; i < size; ++i )
	{
		if( *currentPtr < currentPtr[i] )
		{
			currentPtr = &currentPtr[i];
		}
		else
		{
			++currentPtr;
		}
	}
	return &currentPtr;
}

Swap( int* currentPtr, int* smallestCorrectPtr )
{
	int temp = 0;

	temp = *(smallestCorrectPtr+1);
	*(smallestCorrectPtr+1) = *currentPtr;
	*currentPtr = temp;
}
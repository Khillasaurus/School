?//Not Working Yet!!!

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FillList( int*, int );
void PrintList( int*, int );

int main()
{
	const int listSize = 16;
	int groupSize = 2;
	int list[listSize];
	int* tempPtr = list;
	int tempHolder = 0;
	int smallest = 0;

	FillList( tempPtr, listSize );
	printf("List Before:\n");
	PrintList( tempPtr, listSize );
	printf("\n\n");
	
	while( groupSize < listSize )
	{
		for( int i = 0; i < listSize; i+groupSize )
		{
			if( list[i] > list[i+1] )
			{
				//selection sort
				for( int j = 0; j < groupSize; ++j )
				{
					if( list[i+j] < list[i] )
					{
						tempHolder = list[i];
						list[i] = list[i+j];
						list[i+j] = tempHolder;

					}//end if
				}//end inner for
			}//end if
		}//end outer for
	groupSize *= 2;
	}//end while

	printf("List After:\n");
	PrintList( tempPtr, listSize );

}

void FillList( int* tempPtr, int listSize )
{
	for( int i = 0; i < listSize; ++i )
	{
		tempPtr[i] = rand() % 101;
	}
}

void PrintList( int* tempPtr, const int listSize)
{
	for( int i = 0; i < listSize; ++i )
	{
		printf( "%d\n", tempPtr[i] );
	}

}
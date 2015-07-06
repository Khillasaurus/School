//-----------------------------------
// File:		inclassbubblesort.cpp
// Created:		2012/05/10
// Copyright:	Daniel Schenker
//-----------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "conio.h"

#define SIZE 10

//Function Prototypes
void BubbleSort(int[], int);
void SelectionSort(int[], int);

int main()
{
	int myArray[SIZE];
	srand((unsigned)time(NULL));

	//Create an array with random values
	for(int i = 0; i < SIZE; ++i)
	{
		myArray[i] = rand() % 90 + 10;
	}

	//Print unsorted array
	printf("Unsorted array:\t");
	for(int i = 0; i < SIZE; ++i)
	{
		printf("%d ", myArray[i]);
	}
	printf("\n");

	//Sort it
	BubbleSort(myArray, SIZE);

	//Print sorted array
	printf("Sorted array:\t");
	for(int i = 0; i < SIZE; ++i)
	{
		printf("%d ", myArray[i]);
	}
	printf("\n");

	return 0;
}

void BubbleSort(int myArray[], int size)
{
	int hold = 0;

	for(int i = (size - 1); i > 0; --i)
	{
		for(int j = 1; j <= i; ++j)
		{
			if(myArray[j-1] > myArray[j])
			{
				hold = myArray[j-1];
				myArray[j-1] = myArray[j];
				myArray[j] = hold;
			}
		}
	}
}

void SelectionSort(int myArray[], int size)
{
	int anArray[nSize] = { 30, 50, 20, 10, 40 };

	// Step through each element of the array
	for(int nStartIndex = 0; nStartIndex < size; nStartIndex++)
	{
		// nSmallestIndex is the index of the smallest element
		// we've encountered so far.
		int nSmallestIndex = nStartIndex;

		// Search through every element starting at nStartIndex+1
		for (int nCurrentIndex = nStartIndex + 1; nCurrentIndex < nSize; nCurrentIndex++) 
		{
			// If the current element is smaller than our previously found smallest
			if (myArray[nCurrentIndex] < myArray[nSmallestIndex])
			{
				// Store the index in nSmallestIndex 
				nSmallestIndex = nCurrentIndex; 
			}
		}
		// Swap our start element with our smallest element 
		swap(myArray[nStartIndex], myArray[nSmallestIndex]);
	}
}

void SelectSort(int myArray[], int size)
{
	for(int i = 0; i < length - 1; ++i)
	{
		smallest = i;
		for(int j = 0; j < length; ++j)
		{
			if(myArray[j]< myArray[smallest])
			{
				smallest = j;
			}
			swap(smallest)
		}
	}
}
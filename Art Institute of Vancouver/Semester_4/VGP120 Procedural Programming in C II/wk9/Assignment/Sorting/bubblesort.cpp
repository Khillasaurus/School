//--------------------------------
// File:		infixtopostfix.cpp
// Created:		2012/05/10
// Copyright:	Daniel Schenker
//--------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>

enum SortFlags
{
	NO_DEBUG_INFO = 0,
	USE_DEBUG_INFO = 1,
};

struct cNode
{
	int data;
	cNode* pNext;
};

//=---Function Prototypes---=
 //Linked List
 //Array
int* CreateArray();
void BubbleSort(int*, const int);
void BubbleSort(int*, const int, const int);
void PrintArray(int*, const int);

int main()
{
	//Create list that needs to be sorted
	const int kArrayLength = 8;
	int array[kArrayLength] = {3, 5, 2, 8, 7, 1, 4, 6};
	int* pArray = &array[0];

	//int* pArray CreateArray		CONTINUE WORKING HERE!!!!!!!!!!!!

	printf("Printing the unsorted list...\n");
	PrintArray(pArray, kArrayLength);

	printf("\nStarting Bubble Sort...\n");
	BubbleSort(pArray, kArrayLength, SortFlags::USE_DEBUG_INFO);

	printf("\nPrinting the sorted list...\n");
	PrintArray(pArray, kArrayLength);

	printf("\n");
}

void BubbleSort(int* pArray, const int kArrayLength)
{
	int hold = 0;
	int checks = kArrayLength;
	bool sorted = false;

	//Perform passes until list is sorted (maximum passes equal to the amount of elements in the list)
	for(int pass = 1; pass < kArrayLength; ++pass)
	{
		printf("Starting pass #%d\n", pass);

		//Array is considered sorted until an unordered pair is found, allowing for an early out if no unordered pairs are found
		sorted = true;

		//Loop through list to "bubble" higher values to the end of the list
		for(int j = 1; j < checks; ++j)
		{
			//if elements in list need to be swapped
			printf("Checking if elements in list need to be swapped...\n");
			printf("element: value\n");
			printf("%d: %d - %d: %d\n", j-1, pArray[j-1], j, pArray[j]);
			if(pArray[j-1] > pArray[j])
			{
				sorted = false;

				printf("Array element %d is greater than element %d. Swapping...\n", j-1, j);
				//Swap
				hold = pArray[j];
				pArray[j] = pArray[j-1];
				pArray[j-1] = hold;
				printf("Done swapping\n");
			}
			else
			{
				printf("Current two elements already in order. Continuing algorithm...");
			}
			printf("DEBUG: Printing current state of list\n");
			PrintArray(pArray, kArrayLength);
		}
		//If the entire list is already sorted, break out of sorting algorithm
		if(sorted)
		{
			break;
		}

		//Perform one less check with each pass as each pass will have one more sorted element than the previous pass
		--checks;
	}
	printf("Done sorting\n");
}

void BubbleSort(int* pArray, const int kArrayLength, const int flag)
{
	if(flag == 1)
	{
		BubbleSort(pArray, kArrayLength);
	}
	else if(flag == 0)
	{
		int hold = 0;
		int checks = kArrayLength;
		bool sorted = false;

		//Perform passes until list is sorted (maximum passes equal to the amount of elements in the list)
		for(int pass = 1; pass < kArrayLength; ++pass)
		{
			//Array is considered sorted until an unordered pair is found, allowing for an early out if no unordered pairs are found
			sorted = true;

			//Loop through list to "bubble" higher values to the end of the list
			for(int j = 1; j < checks; ++j)
			{
				//if elements in list need to be swapped
				if(pArray[j-1] > pArray[j])
				{
					sorted = false;

					//Swap
					hold = pArray[j];
					pArray[j] = pArray[j-1];
					pArray[j-1] = hold;
				}
			}
			//If the entire list is already sorted, break out of sorting algorithm
			if(sorted)
			{
				break;
			}

			//Perform one less check with each pass as each pass will have one more sorted element than the previous pass
			--checks;
		}
	}
}

void PrintArray(int* pArray, const int kArrayLength)
{
	for(int i = 0; i < kArrayLength; ++i)
	{
		printf("%d, ", pArray[i]);
	}
	printf("\n");
}
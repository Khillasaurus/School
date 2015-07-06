//--------------------------------
// File:		CompareSorts.cpp
// Created:		2012/05/30
// Copyright:	Daniel Schenker
//--------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <time.h>

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
bool CreateList(int*&, int&);
bool CreateList(cNode*&, int&);
void BubbleSort(int*, const int);
void BubbleSort(cNode* const, const int);
void BubbleSort(int*, const int, const int);
void BubbleSort(cNode* const, const int, const int);
void SelectionSort(int*, const int);
void SelectionSort(int*, const int, const int);
void PrintList(int*, const int);
void PrintList(const cNode*);
 //Utitity
bool UserAgrees();
void EnsurePositive(int&);
void EnsureValueWithinBoundaries(int&, const int, const int);
void CleanUp(int*&);
void CleanUp(cNode*&);

int main()
{
	srand((unsigned)time(0));

	int startTime = 0;
	int endTime = 0;
	int listLength = 0;
	int choice = 0;

	printf("Would you like to run a sort test using an array? If not a linked list will be used.\n");
	if(UserAgrees())
	{
		int* pArray = NULL;

		//If the array was created succesfully
		if(CreateList(pArray, listLength))
		{
			//Print out unsorted list
			printf("Printing the unsorted list:\n");
			PrintList(pArray, listLength);

			//Determine which sort to use
			printf("Which sort would you like to use?\n");
			printf("1: BubbleSort\n");
			printf("2: SelectionSort\n");
			printf("3: Compare all sorts\n");
			scanf("%d", &choice);
			EnsureValueWithinBoundaries(choice, 1, 3);

			printf("Would you like to sort while viewing debugging comments?\n");
			if(UserAgrees())
			{
				if(choice == 1)
				{
					startTime = clock();
					printf("\nStarting Bubble Sort\n");
					//Sort with debugging info
					BubbleSort(pArray, listLength, SortFlags::USE_DEBUG_INFO);
					endTime = clock();
				}
				else if(choice == 2)
				{
					startTime = clock();
					printf("\nStarting Selection Sort\n");
					//Sort with debugging info
					SelectionSort(pArray, listLength, SortFlags::USE_DEBUG_INFO);
					endTime = clock();	
				}
				else if(choice == 3)
				{
					int startTime2 = 0;
					int endTime2 = 0;

					//Create a copy of the original list to sort
					int* pArray2 = (int*)malloc(listLength * sizeof(int));
					for(int i = 0; i < listLength; ++i)
					{
						pArray2[i] = pArray[i];
					}

					startTime = clock();
					printf("\nStarting Bubble Sort\n");
					//Sort with debugging info
					BubbleSort(pArray, listLength, SortFlags::USE_DEBUG_INFO);
					endTime = clock();

					//Print out sorted list
					printf("\nPrinting the Bubble sorted list:\n");
					PrintList(pArray, listLength);

					printf("It took %d clock cycles to perform the Bubble sort.\n", endTime - startTime);

					startTime2 = clock();
					printf("\nStarting Selection Sort\n");
					//Sort with debugging info
					SelectionSort(pArray, listLength, SortFlags::USE_DEBUG_INFO);
					endTime2 = clock();

					//Print out sorted list
					printf("\nPrinting the Selection sorted list:\n");
					PrintList(pArray, listLength);

					printf("It took %d clock cycles to perform the Selection sort.\n", endTime2 - startTime2);

					printf("Selection sort was %d% faster than Bubble sort.\n", (1 - ((endTime2 - startTime2) - (endTime - startTime))) * 100);

				}
			}
			else
			{
				if(choice == 1)
				{
					startTime = clock();
					//Sort with debugging info
					BubbleSort(pArray, listLength, SortFlags::NO_DEBUG_INFO);
					endTime = clock();
				}
				else if(choice == 2)
				{
					startTime = clock();
					//Sort with debugging info
					SelectionSort(pArray, listLength, SortFlags::NO_DEBUG_INFO);
					endTime = clock();	
				}
				else if(choice == 3)
				{
					int startTime2 = 0;
					int endTime2 = 0;

					//Create a copy of the original list to sort
					int* pArray2 = (int*)malloc(listLength * sizeof(int));
					for(int i = 0; i < listLength; ++i)
					{
						pArray2[i] = pArray[i];
					}

					startTime = clock();
					//Sort with debugging info
					BubbleSort(pArray, listLength, SortFlags::NO_DEBUG_INFO);
					endTime = clock();
					printf("It took %d clock cycles to perform the Bubble sort.\n", endTime - startTime);

					startTime2 = clock();
					//Sort with debugging info
					SelectionSort(pArray, listLength, SortFlags::NO_DEBUG_INFO);
					endTime2 = clock();
					printf("It took %d clock cycles to perform the Selection sort.\n", endTime2 - startTime2);

					printf("Selection sort was %f%% faster than Bubble sort.\n", (float)( (float)((float)(endTime2 - startTime2) / (float)(endTime - startTime)) * 100) );
				}
			}

			if(choice != 3)
			{
				//Print out sorted list
				printf("\nPrinting the sorted list:\n");
				PrintList(pArray, listLength);
			}

			printf("\n");
		}
		else
		{
			printf("ERROR: Could not create the array. Exiting. - CreateList(pArray, listLength) in main() failed.\n");
			return -1;
		}
	}
	else
	{
		cNode* pList = NULL;

		//If the array was created succesfully
		if(CreateList(pList, listLength))
		{
			//Print out unsorted list
			printf("Printing the unsorted list:\n");
			PrintList(pList);

			printf("Would you like to sort while viewing debugging comments?\n");
			if(UserAgrees())
			{
				startTime = clock();
				printf("\nStarting Bubble Sort\n");
				//Sort with debugging info
				BubbleSort(pList, listLength, SortFlags::USE_DEBUG_INFO);
				endTime = clock();
			}
			else
			{
				startTime = clock();
				//Sort without debugging info
				BubbleSort(pList, listLength, SortFlags::NO_DEBUG_INFO);
				endTime = clock();
			}

			//Print out sorted list
			printf("\nPrinting the sorted list:\n");
			PrintList(pList);

			printf("\n");
		}
		else
		{
			printf("ERROR: Could not create the list. Exiting. - CreateList(pList, listLength) in main() failed.\n");
			return -1;
		}
	}

	if(choice != 3)
	{
		printf("It took %d clock cycles to perform the sort.\n", endTime - startTime);
	}

	return 0;
}

bool CreateList(int*& pArray, int& arrayLength)
{
	//Determine array length
	printf("How long is the array that you would like to sort?\n");
	scanf("%d", &arrayLength);
	EnsurePositive(arrayLength);

	//Allocate memory for array
	pArray = (int*)malloc(arrayLength * sizeof(int));

	//If memory was allocated succesfully
	if(pArray)
	{
		//Determine if array values should be entered manually or generated randomly
		printf("Would you like to enter the array values manually, or generate them randomly?\n");
		printf("Enter 1 to enter manually, 0 to generate randomly.\n");
		//If data array values are being generated manually
		if(UserAgrees())
		{
			//Get array values from user
			for(int i = 0; i < arrayLength; ++i)
			{
				printf("Enter value for element %d: ", i);
				scanf("%d", &(pArray[i]));
				printf("\n");
			}
		}
		//Generate array values randomly
		else
		{
			int min = 0;
			int max = 0;
			int range = 0;
			//Determine min and max values in array
			printf("Please enter the minimum and maximum values allowed in the array.\n");
			printf("Minimum: ");
			scanf("%d", &min);
			printf("\n");
			printf("Maximum: ");
			scanf("%d", &max);
			printf("\n");
			//Ensure maximum value is greater than the minimum value
			EnsureValueWithinBoundaries(max, min, 0x7FFFFFFF);//7FFFFFFF is the maximum postive value for a signed int
			range = (max - min) + 1;

			//Determine if duplicate values are allowed
			printf("Are duplicate values allowed?\n");
			if(UserAgrees())
			{
				//Generate array with duplicate values allowed
				for(int i = 0; i < arrayLength; ++i)
				{
					pArray[i] = min + (rand() % range);
				}
			}
			//Generate array with NO duplicate values allowed
			else
			{
				//Ensure that range allows for all unique numbers
				if(range < arrayLength)
				{
					printf("The range of values that you have restricted is too small for the size of the array you have chosen.\n");
					//Check to see if the maximum value can not be raised sufficiently based on the maximum value of an int
					/*
					If the minimum value + the array length is greater than the maximum value for an int,
					min + arrayLength will overflow into the negative values.
					Therefore checking if min + arrayLength (which is the potential new maximum) is less than the minimum value, an overflow occured,
					and thus a new minimum value will be needed to be chosen.
					*/
					if(min + arrayLength <= min)
					{
						//Get a new minimum value
						printf("Since your maximum value can not be increased sufficiently due to memory constraints, the minimum value must be lowered.\n");
						printf("Minimum: ");
						scanf("%d", &min);
						printf("\n");
						EnsureValueWithinBoundaries(min, 0x80000000, max - arrayLength);//0x80000000 is the minimum value for a signed int
						range = (max - min) + 1;
					}
					//Check to see if the minimum value can not be lowered sufficiently based on the minimum value of an int
					/*
					If the maximum value - the array length is less than the minimum value for an int,
					max - arrayLength will overflow into the positive values.
					Therefore checking if max - arrayLength (which is the potential new minimum) is greater than the maximum value, an overflow occured,
					and thus a new maximum value will be needed to be chosen.
					*/
					else if(max - arrayLength >= max)
					{
						//Get a new maximum value
						printf("Since your minimum value can not be lowered sufficiently due to memory constraints, the maximum value must be raised.\n");
						printf("Maximum: ");
						scanf("%d", &max);
						printf("\n");
						EnsureValueWithinBoundaries(max, min + arrayLength, 0x7FFFFFFF);//0x7FFFFFFF is the maximum postive value for a signed int
						range = (max - min) + 1;
					}
					else
					{
						printf("Would you like to lower the minimum value? (If not you will have to raise the maximum value.\n");
						//Lower minimum
						if(UserAgrees())
						{
							printf("Minimum: ");
							scanf("%d", &min);
							printf("\n");
							EnsureValueWithinBoundaries(min, 0x80000000, max - arrayLength);//0x80000000 is the minimum value for a signed int
							range = (max - min) + 1;
						}
						//Raise maximum
						else
						{
							printf("Maximum: ");
							scanf("%d", &max);
							printf("\n");
							EnsureValueWithinBoundaries(max, min + arrayLength, 0x7FFFFFFF);//0x7FFFFFFF is the maximum postive value for a signed int
							range = (max - min) + 1;
						}
					}
				}
				//Generate list with constraints in place (NO duplicate values allowed)
				for(int i = 0; i < arrayLength; ++i)
				{
					pArray[i] = min + (rand() % range);
					//Loop through previously entered values to check if random value has been used yet
					for(int j = 0; j < i; ++j)
					{
						//If the new random value has been found to of been used earlier in the array
						if(pArray[i] == pArray[j])
						{
							//Generate a new random value
							pArray[i] = min + (rand() % range);
							//Reset search back to beginning of array
							j = 0;
						}
					}
				}
			}
		}
	}
	else
	{
		printf("ERROR: Memory could not be allocated for the array. - CreateList(int*&, int&)\n");
		return false;
	}

	return true;
}

bool CreateList(cNode*& pList, int& listLength)
{
	//Determine list length
	printf("How long is the list that you would like to sort?\n");
	scanf("%d", &listLength);
	EnsurePositive(listLength);

	//Allocate memory for list
	pList = (cNode*)malloc(listLength * sizeof(cNode*));
	pList->pNext = NULL;
	cNode* pTemp = pList;
	for(int i = 0; i < listLength - 1; ++i)
	{
		pTemp->pNext = (cNode*)malloc(listLength * sizeof(cNode*));
		pTemp = pTemp->pNext;
		pTemp->pNext = NULL;
	}

	//If memory was allocated succesfully
	if(pList)
	{
		//Set pTemp to point back to the head of the list again
		pTemp = pList;

		//Determine if list values should be entered manually or generated randomly
		printf("Would you like to enter the list values manually, or generate them randomly?\n");
		printf("Enter 1 to enter manually, 0 to generate randomly.\n");
		//If data list values are being generated manually
		if(UserAgrees())
		{
			//Get list values from user
			for(int i = 0; i < listLength; ++i)
			{
				printf("Enter value for element %d: ", i);
				scanf("%d", &(pTemp->data));
				pTemp = pTemp->pNext;
				printf("\n");
			}
		}
		//Generate list values randomly
		else
		{
			int min = 0;
			int max = 0;
			int range = 0;
			//Determine min and max values in list
			printf("Please enter the minimum and maximum values allowed in the list.\n");
			printf("Minimum: ");
			scanf("%d", &min);
			printf("\n");
			printf("Maximum: ");
			scanf("%d", &max);
			printf("\n");
			//Ensure maximum value is greater than the minimum value
			EnsureValueWithinBoundaries(max, min, 0x7FFFFFFF);//7FFFFFFF is the maximum postive value for a signed int
			range = (max - min) + 1;

			//Determine if duplicate values are allowed
			printf("Are duplicate values allowed?\n");
			if(UserAgrees())
			{
				//Generate list with duplicate values allowed
				while(pTemp)
				{
					pTemp->data = min + (rand() % range);
					pTemp = pTemp->pNext;
				}
			}
			//Generate list with NO duplicate values allowed
			else
			{
				//Ensure that range allows for all unique numbers
				if(range < listLength)
				{
					printf("The range of values that you have restricted is too small for the size of the list you have chosen.\n");
					//Check to see if the maximum value can not be raised sufficiently based on the maximum value of an int
					/*
					If the minimum value + the list length is greater than the maximum value for an int,
					min + listLength will overflow into the negative values.
					Therefore checking if min + listLength (which is the potential new maximum) is less than the minimum value, an overflow occured,
					and thus a new minimum value will be needed to be chosen.
					*/
					if(min + listLength <= min)
					{
						//Get a new minimum value
						printf("Since your maximum value can not be increased sufficiently due to memory constraints, the minimum value must be lowered.\n");
						printf("Minimum: ");
						scanf("%d", &min);
						printf("\n");
						EnsureValueWithinBoundaries(min, 0x80000000, max - listLength);//0x80000000 is the minimum value for a signed int
						range = (max - min) + 1;
					}
					//Check to see if the minimum value can not be lowered sufficiently based on the minimum value of an int
					/*
					If the maximum value - the list length is less than the minimum value for an int,
					max - listLength will overflow into the positive values.
					Therefore checking if max - listLength (which is the potential new minimum) is greater than the maximum value, an overflow occured,
					and thus a new maximum value will be needed to be chosen.
					*/
					else if(max - listLength >= max)
					{
						//Get a new maximum value
						printf("Since your minimum value can not be lowered sufficiently due to memory constraints, the maximum value must be raised.\n");
						printf("Maximum: ");
						scanf("%d", &max);
						printf("\n");
						EnsureValueWithinBoundaries(max, min + listLength, 0x7FFFFFFF);//0x7FFFFFFF is the maximum postive value for a signed int
						range = (max - min) + 1;
					}
					else
					{
						printf("Would you like to lower the minimum value? (If not you will have to raise the maximum value.\n");
						//Lower minimum
						if(UserAgrees())
						{
							printf("Minimum: ");
							scanf("%d", &min);
							printf("\n");
							EnsureValueWithinBoundaries(min, 0x80000000, max - listLength);//0x80000000 is the minimum value for a signed int
							range = (max - min) + 1;
						}
						//Raise maximum
						else
						{
							printf("Maximum: ");
							scanf("%d", &max);
							printf("\n");
							EnsureValueWithinBoundaries(max, min + listLength, 0x7FFFFFFF);//0x7FFFFFFF is the maximum postive value for a signed int
							range = (max - min) + 1;
						}
					}
				}
				//Generate list with constraints in place (NO duplicate values allowed)
				cNode* pTemp2 = pList;
				for(int i = 0; i < listLength; ++i)
				{
					pTemp->data = min + (rand() % range);
					//Reset search back to beginning of list
					pTemp2 = pList;
					//Loop through previously entered values to check if random value has been used yet
					for(int j = 0; j < i; ++j)
					{
						//If the new random value has been found to of been used earlier in the list
						if(pTemp->data == pTemp2->data)
						{
							//Generate a new random value
							pTemp->data = min + (rand() % range);
							//Reset search back to beginning of list
							j = 0;
							pTemp2 = pList;
						}
						if(j != 0)
						{
							//As j moves forward, move the pointer with it
							pTemp2 = pTemp2->pNext;
						}
					}
					//As i moves forward, move the pointer with it
					pTemp = pTemp->pNext;
				}
			}
		}
	}
	else
	{
		printf("ERROR: Memory could not be allocated for the list. - CreateList(cNode*&, int&)\n");
		return false;
	}

	return true;
}

void BubbleSort(int* pArray, const int kArrayLength)
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

void BubbleSort(cNode* const pList, const int kListLength)
{
	cNode* pTemp = pList;
	cNode* pTemp2 = pList;//pTemp2 points to the node before pTemp

	int hold = 0;
	int checks = kListLength;
	bool sorted = false;

	//Perform passes until list is sorted (maximum passes equal to the amount of elements in the list)
	for(int pass = 1; pass < kListLength; ++pass)
	{
		//List is considered sorted until an unordered pair is found, allowing for an early out if no unordered pairs are found
		sorted = true;

		//Set pTemp and pTemp2 to the beginning of the list
		pTemp = pList;
		pTemp2 = pList;
		//Set pTemp to point to the second node in the list
		pTemp = pTemp->pNext;
		//Loop through list to "bubble" higher values to the end of the list
		for(int j = 1; j < checks; ++j)
		{
			//if elements in list need to be swapped
			if(pTemp2->data > pTemp->data)
			{
				sorted = false;

				//Swap
				hold = pTemp->data;
				pTemp->data = pTemp2->data;
				pTemp2->data = hold;
			}

			//As j moves forward, move the pointers with it
			pTemp = pTemp->pNext;
			pTemp2 = pTemp2->pNext;
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

void BubbleSort(int* pArray, const int kArrayLength, const int flag)
{
	if(flag == USE_DEBUG_INFO)
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
				printf("Checking if elements in list need to be swapped\n");
				printf("element: value\n");
				printf("%d: %d - %d: %d\n", j-1, pArray[j-1], j, pArray[j]);
				if(pArray[j-1] > pArray[j])
				{
					sorted = false;

					printf("Array element %d is greater than element %d. Swapping\n", j-1, j);
					//Swap
					hold = pArray[j];
					pArray[j] = pArray[j-1];
					pArray[j-1] = hold;
					printf("Done swapping\n");
				}
				else
				{
					printf("Current two elements already in order. Continuing algorithm\n");
				}
				printf("Printing current state of list:\n");
				PrintList(pArray, kArrayLength);
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
	else if(flag == NO_DEBUG_INFO)
	{
		BubbleSort(pArray, kArrayLength);
	}
}

void BubbleSort(cNode* const pList, const int kListLength, const int flag)
{
	cNode* pTemp = pList;
	cNode* pTemp2 = pList;//pTemp2 points to the node before pTemp
	if(flag == USE_DEBUG_INFO)
	{
		int hold = 0;
		int checks = kListLength;
		bool sorted = false;

		//Perform passes until list is sorted (maximum passes equal to the amount of elements in the list)
		for(int pass = 1; pass < kListLength; ++pass)
		{
			printf("Starting pass #%d\n", pass);

			//List is considered sorted until an unordered pair is found, allowing for an early out if no unordered pairs are found
			sorted = true;

			//Set pTemp and pTemp2 to the beginning of the list
			pTemp = pList;
			pTemp2 = pList;
			//Set pTemp to point to the second node in the list
			pTemp = pTemp->pNext;
			//Loop through list to "bubble" higher values to the end of the list
			for(int j = 1; j < checks; ++j)
			{
				//if elements in list need to be swapped
				printf("Checking if elements in list need to be swapped\n");
				printf("element: value\n");
				printf("%d: %d - %d: %d\n", j-1, pTemp2->data, j, pTemp->data);
				if(pTemp2->data > pTemp->data)
				{
					sorted = false;

					printf("List element %d is greater than element %d. Swapping\n", j-1, j);
					//Swap
					hold = pTemp->data;
					pTemp->data = pTemp2->data;
					pTemp2->data = hold;
					printf("Done swapping\n");
				}
				else
				{
					printf("Current two elements already in order. Continuing algorithm\n");
				}
				printf("Printing current state of list:\n");
				PrintList(pList);

				//As j moves forward, move the pointers with it
				pTemp = pTemp->pNext;
				pTemp2 = pTemp2->pNext;
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
	else if(flag == NO_DEBUG_INFO)
	{
		BubbleSort(pList, kListLength);
	}
}

void SelectionSort(int* pArray, const int kArrayLength)
{
	int hold = 0;
	int lowest = 0;

	//find the lowest element in the array
	for(int j = 0; j < kArrayLength - 1; ++j)
	{
		//assume the first element is the lowest
		lowest = j;
		//Compare elements after j to find the smallest value
		for(int i = j + 1; i < kArrayLength; ++i)
		{
			//if this element is less, then it is the new minimum
			if(pArray[i] < pArray[lowest])
			{
				//found new minimum; remember its index
				lowest = i;
			}
		}
		//lowest is the index of the minimum element. Swap it with the current position
		if(lowest != j)
		{
			//Swap
			hold = pArray[j];
			pArray[j] = pArray[lowest];
			pArray[lowest] = hold;
		}
	}
}

void SelectionSort(int* pArray, const int kArrayLength, const int flag)
{
	if(flag == USE_DEBUG_INFO)
	{
		int hold = 0;
		int lowest = 0;

		//find the lowest element in the array
		for(int j = 0; j < kArrayLength - 1; ++j)
		{
			printf("Starting pass #%d\n", j);

			//assume the first element is the lowest
			lowest = j;
			//Compare elements after j to find the smallest value
			for(int i = j + 1; i < kArrayLength; ++i)
			{
				//if this element is less, then it is the new minimum
				printf("Checking if current element is the new lowest value\n");
				printf("current element: value - lowest index: lowest value\n");
				printf("%d: %d - %d: %d\n", i, pArray[i], lowest, pArray[lowest]);
				if(pArray[i] < pArray[lowest])
				{
					//found new minimum; remember its index
					lowest = i;
				}
			}
			//lowest is the index of the minimum element. Swap it with the current position
			if(lowest != j)
			{
				printf("Array element %d is greater than element %d. Swapping\n", lowest, j);
				//Swap
				hold = pArray[j];
				pArray[j] = pArray[lowest];
				pArray[lowest] = hold;
			}
			else
			{
				printf("Current two elements already in order. Continuing algorithm\n");
			}
			printf("Printing current state of array:\n");
			PrintList(pArray, kArrayLength);
		}
		printf("Done sorting\n");	
	}
	else if(flag == NO_DEBUG_INFO)
	{
		SelectionSort(pArray, kArrayLength);
	}
}

void PrintList(int* pArray, const int kArrayLength)
{
	for(int i = 0; i < kArrayLength; ++i)
	{
		printf("%d, ", pArray[i]);
	}
	printf("\n");
}

void PrintList(const cNode* pList)
{
	//while not at the end of the list 
	while(pList)
	{
		//Print the data inside the current node
		printf("%d, ", pList->data);
		//Move the list pointer forward
		pList = pList->pNext;
	}
	printf("\n");
}

 //===---Utility---===

bool UserAgrees()
{
	printf("Enter 1 for yes, 0 for no.\n");

	int choice = -1;
	while(choice < 0 || choice > 1)
	{
		scanf("%d", &choice);
		if(choice < 0 || choice > 1)
		{
			printf("Invalid option. Please choose again.\n");
		}
	}

	if(choice == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void EnsurePositive(int& choice)
{
	while(choice < 0)
	{
		printf("Invalid option. You must enter a positive value.\n");
		printf("Please choose again.\n");
		scanf("%d", choice);
	}
}

void EnsureValueWithinBoundaries(int& value, const int lower, const int upper)
{
	while(value < lower || value > upper)
	{
		if(value < lower)
		{
			printf("Invalid value. You must enter a value greater than %d.\n", (lower - 1));
			scanf("%d", &value);
		}
		else if(value > upper)
		{
			printf("Invalid value. You must enter a value less than %d.\n", (upper + 1));
			scanf("%d", &value);
		}
	}
}

void CleanUp(int*& pArray)
{
	free(pArray);
	pArray = NULL;
}

void CleanUp(cNode*& pList)
{
	cNode* pTemp = NULL;

	//While pList is not pointing to the last node
	while(pList)
	{
		pTemp = pList;
		pList = pList->pNext;
		free(pTemp);
		pTemp = NULL;
	}
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

//function prototypes
int* CreateList(int*&, int&);
void PrintList(const int*, const int);
void Search(int*, int&, int&, int&, int&);

int main()
{
	//initialize random seed
	srand((unsigned)time(NULL));

	int* pList;
	int listSize = 0;
	int first;
	int last;
	int value;
	int middle;

	pList = CreateList(pList, listSize);
	PrintList(pList, listSize);
	Search(pList, first, last, value, middle);

	return 0;
}




int* CreateList(int*& pList, int& listSize)
{
	while(listSize < 1)
	{
		printf("How long an list would you like?\n");
		scanf("%d", &listSize);
		if(listSize < 1)
		{
			printf("You have entered an invalid value.\n");
		}
	}
	printf("A list of size %d will be created with random numbers between 1 and 99 inclusive.\n", listSize);
	pList = (int*)malloc(sizeof(int)*listSize);
	
	for(int i = 0; i < listSize; ++i)
	{
		pList[i] = rand() % 99 + 1;
	}

	return pList;
}




void PrintList(const int* head, const int size)
{
	printf("The list:\n");
	for(int i = 0; i < size; ++i)
	{
		printf("%d: %d\n", i, head[i]);
	}
	printf("\n");
}




void Search(int* pList, int& first, int& last, int& value, int& middle)
{
	printf("What value would you like to search for?\n");
	scanf("%d", &value);

	while(first < last)
	{
		middle = (first + last) / 2;
		
		if(pList[middle] == value)
		{
			printf(" Found value.\n");
			break;
		}
		else if(pList[middle] < value)
		{
		last = middle - 1;
		}
		else
		{
			first = middle + 1;
		}
	}
		if(last < first)
		{
			printf("Could not find value.\n");
		}
}
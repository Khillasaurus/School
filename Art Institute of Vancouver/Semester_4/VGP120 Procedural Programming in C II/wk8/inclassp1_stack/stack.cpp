//-----------------------------
// File:		inclassp1.cpp
// Created:		2012/05/10
// Copyright:	Daniel Schenker
//-----------------------------

#include <stdio.h>
#include <stdlib.h>

struct cNode
{
	int data;
	cNode* beneath;
};

//=---Function Prototypes---=
 //Program Specific
int Instructions();
void Push(cNode*&);
void Push(cNode*&, const int);
void Pop(cNode*&);
void PrintStack(cNode*);
int StackLength(cNode* const);
bool IsEmpty(const cNode* const);
void CleanUp(cNode* pTop);
 //Utility
void EnsureWithinBoundaries(int&, const int, const int);

int main()
{
	cNode* pTop = NULL;
	
	while(1)
	{
		switch(Instructions())
		{
		case 0:
			return 0;
		case 1:
			Push(pTop);
			break;
		case 2:
			Pop(pTop);
			break;
		case 3:
			PrintStack(pTop);
			break;
		case 4:
			printf("The stack length is: %d.\n", StackLength(pTop));
			break;
		default:
			printf("ERROR: Invalid input given.\n");
			printf("Please enter a new choice from the instructions list.\n");
			break;
		}
	}
	CleanUp(pTop);

	return 0;
}

int Instructions()
{
	int choice = -1;
	printf("\nWhat would you like to do?\n");
	printf("1: Push\n");
	printf("2: Pop\n");
	printf("3: Print\n");
	printf("4: Length\n");
	printf("0: Quit.\n");
	scanf_s("%d", &choice);
	EnsureWithinBoundaries(choice, 0, 4);

	return choice;
}

void Push(cNode*& pTop)
{
	cNode* pTemp = (cNode*)malloc(sizeof(cNode));
	pTemp->beneath = pTop;
	pTop = pTemp;

	printf("Enter the value that you would you like to add:\n");
	scanf_s("%d", &(pTop->data));
}

void Push(cNode*& pTop, const int value)
{
	cNode* pTemp = (cNode*)malloc(sizeof(cNode));
	pTemp->beneath = pTop;
	pTop = pTemp;
	pTop->data = value;
}

void Pop(cNode*& pTop)
{
	//If the stack is empty
	if(!pTop)
	{
		printf("ERROR: Could not pop from the top of the stack as the stack pointer equals NULL. - Pop(cNode*& pTop)\n");
	}
	else
	{
		cNode* pTemp = pTop->beneath;
		free(pTop);
		pTop = pTemp;
	}
}

int StackLength(cNode* const pTop)
{
	cNode* pTemp = pTop;
	int stackLength = 0;

	//while pTemp has not reached the bottom of the stack
	while(pTemp)
	{
		++stackLength;
		//if pTemp is not at the bottom of the stack
		if(pTemp->beneath)
		{
			pTemp = pTemp->beneath;
		}
		else
		{
			return stackLength;
		}
	}
	return stackLength;
}

void PrintStack(cNode* const pTop)
{
	cNode* pTemp = pTop;
	bool isEmpty = true;

	printf("The stack:");
	if(!pTemp)
	{
		if(isEmpty)
		{
			printf(" empty.\n");
		}
		return;
	}
	else
	{
		isEmpty = false;
		printf("\n");
	}

	//while pTemp is not pointing to the bottom of the stack
	while(pTemp->beneath)
	{
		printf("%d\n", pTemp->data);
		pTemp = pTemp->beneath;
	}
	printf("%d\n", pTemp->data);
}

bool IsEmpty(const cNode* const pTop)
{
	//If the stack exists
	if(pTop)
	{
		return false;
	}
	else//the stack is empty
	{
		return true;
	}
}

void CleanUp(cNode* pTop)
{
	cNode* pTemp;

	//while the stack is not empty
	while(pTop)
	{
		pTemp = pTop;
		pTop = pTop->beneath;
		free(pTemp);
	}
}

void EnsureWithinBoundaries(int& answer, const int lower, const int upper)
{
	while(answer < lower || answer > upper)
	{
		if(answer < lower)
		{
			printf("Invalid answer. You must enter a value greater than %d.\n", (lower - 1));
			scanf_s("%d", &answer);
		}
		else if(answer > upper)
		{
			printf("Invalid answer. You must enter a value less than %d.\n", (upper + 1));
			scanf_s("%d", &answer);
		}
	}
}

//How to be a Joseph:
// %-\0_0\| <-Joseph	To the left!
/// %-\0_0\| <-Joseph	to the left!
// |/0_0/-% <-Joseph	To the right!
/// |/0_0/-% <-Joseph	To the right!
// %-\0_0/-% <-Joseph	To the windows!
/// |/0_0/-% <-Joseph	to the walls!
/// %-\0_0\| <-Joseph	to the sweat drop down my balls!
// %-\0_0/-% <-Joseph   Eyyyoo!
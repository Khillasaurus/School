//-----------------------------
// File:		inclassp1.cpp
// Created:		2012/05/10
// Copyright:	Daniel Schenker
//-----------------------------

#include <stdio.h>
#include <stdlib.h>

struct TreeNode
{
	int data;
	TreeNode* leftPtr;
	TreeNode* rightPtr;
};

//=---Function Prototypes---=
 //Program Specific
int Instructions();
void InsertNode(TreeNode**, int);
int FindGreatest(TreeNode*);
void PrintTree(TreeNode*);
void PrintTree(TreeNode**);
 //Utitity
void EnsureWithinBoundaries(int&, const int, const int);

int main()
{
	TreeNode* root = NULL;
	int number = 0;
	int nodeCount = 0;
	
	while(1)
	{
		switch(Instructions())
		{
		case 0:
			return 0;
		case 1:
			do
			{
				printf("Please Enter a Number (0 to return): ");
				scanf("%d", &number);
				if(number > 0)
				{
					InsertNode(&root, number);
					++nodeCount;
				}
				else if(number != 0)
				{
					printf("You have entered an invalid number.\n");
				}
			}while(number != 0);
			break;
		case 2:
			printf("The Tree:\n");
			PrintTree(root);
			//PrintTree(&root);//Overloaded function, showing here to remind that using this function is also an option
			break;
		case 3:
			printf("The greatest value in the tree: %d\n", FindGreatest(root));
			break;
		default:
			printf("ERROR: Invalid input given.\n");
			printf("Please enter a new choice from the instructions list.\n");
			break;
		}
	}


	return 0;
}

int Instructions()
{
	int choice = -1;
	printf("\nWhat would you like to do?\n");
	printf("1: Add a number to the tree.\n");
	printf("2: Print the entire tree in order.\n");
	printf("3: Print the greatest value in the tree.\n");
	printf("0: Quit.\n");
	scanf("%d", &choice);
	EnsureWithinBoundaries(choice, 0, 3);

	return choice;
}

void InsertNode(TreeNode** treePtr, int value)
{
	//If the tree is empty
	if(!(*treePtr))
	{
		//Allocate memory for new node
		*treePtr = (TreeNode*)malloc(sizeof(TreeNode));
		//Check if memory was allocated
		if(!(*treePtr))
		{
			printf("Error, out of memory\n");
			return;
		}
		(*treePtr)->data = value;
		(*treePtr)->leftPtr = NULL;
		(*treePtr)->rightPtr = NULL;
	}
	else
	{
		//If the value we are trying to add is...
		//...smaller than the current node's data
		if(value < (*treePtr)->data)
		{
			InsertNode(&((*treePtr)->leftPtr), value);
		}
		//...greater than the current node's data
		else if(value > (*treePtr)->data)
		{
			InsertNode(&((*treePtr)->rightPtr), value);
		}
		//...already exists in the tree
		else
		{
			printf("That data already exists in the tree!\n");
		}
	}
}

int FindGreatest(TreeNode* treePtr)
{
	//Create temporary pointer to prevent loss of the tree root
	TreeNode* tempPtr = treePtr;
	int greatest = tempPtr->data;

	//While not at furthest right node
	while(tempPtr->rightPtr)
	{
		//Move the pointer to the right
		tempPtr = tempPtr->rightPtr;
	}
	greatest = tempPtr->data;

	return greatest;
}

void PrintTree(TreeNode* rootPtr)
{
	//If the root node exists
	if(rootPtr)
	{
		//Work way down left side of tree
		PrintTree(rootPtr->leftPtr);
		//Print middle value (root) of tree
		printf("%d\n", rootPtr->data);
		//Work way down right side of tree
		PrintTree(rootPtr->rightPtr);
	}
}

void PrintTree(TreeNode** rootPtr)
{
	//If the root node exists
	if(*rootPtr)
	{
		//Work way down left side of tree
		PrintTree(&((*rootPtr)->leftPtr));
		//Print middle value (root) of tree
		printf("%d\n", (*rootPtr)->data);
		//Work way down right side of tree
		PrintTree(&((*rootPtr)->rightPtr));
	}
}

void EnsureWithinBoundaries(int& answer, const int lower, const int upper)
{
	while(answer < lower || answer > upper)
	{
		if(answer < lower)
		{
			printf("Invalid answer. You must enter a value greater than %d.\n", (lower - 1));
			scanf("%d", &answer);
		}
		else if(answer > upper)
		{
			printf("Invalid answer. You must enter a value less than %d.\n", (upper + 1));
			scanf("%d", &answer);
		}
	}
}
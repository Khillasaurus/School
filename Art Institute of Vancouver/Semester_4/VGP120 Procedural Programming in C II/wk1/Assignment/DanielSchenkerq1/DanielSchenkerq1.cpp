//-----------------------------
// File:		DanielSchenkerq1.cpp
// Created:		2012/04/05
// Copyright:	Daniel Schenker
//-----------------------------

//Note: Comments in the cpp may or may not be trivial

#include "stdio.h"
#include <iostream>

using namespace std;

//------------FUNCTION PROTOTYPES-------------
int QueryData();							// Returns an int which is the length of the side of a box
char* CreateBox(const int*);				// Returns a char pointer to a newly allocated box
void DisplayBox(const char*, const int*);	// Prints a box to the console using ascii art
int Square(const int);						// Returns an int which is the square of a number
bool CleanUp(char*&);						// Frees allocated memory in the heap by sending a char pointer to the function, and returns whether deallocation was succesful or not

int main()
{
	int sideLength = QueryData();			// Length of side of box
	const int* pSideLength = &sideLength;	// Constant pointer to to length of side of box
	char* pBox = CreateBox(pSideLength);	// Char pointer to box
	DisplayBox(pBox, pSideLength);
	CleanUp(pBox);

	return 0;
}

// Returns an int which is the length of the side of a box
int QueryData()
{
	int sideLength = 0;
	// Check to ensure the side length of the box is not 0 or less
	while(sideLength < 1)
	{
		cout << "How long would you like the side of the box to be?" << endl;
		cin >> sideLength;
		if(sideLength < 1)
		{
			cout << "Invalid input given. Please enter a new value." << endl;
		}
	}
	return sideLength;
}

// Takes in an int pointer to the length of side of box
char* CreateBox(const int* pSideLength)
{
	const int kArrayLength = Square(*pSideLength);// Determine how many elements are needed for array in next line
	char* pBox = new (nothrow) char[kArrayLength];// Allocate a single subscripted array to store box data in

	// If pBox has been allocated succsefully
	if(!pBox)
	{
		cout << "ERROR: Unable to allocate memory for box." << endl << "Returning null pointer instead." << endl;
		return pBox;
	}
	else
	{
		// Sets every element of pBox to '*'
		for(int i = 0; i < kArrayLength; ++i)
		{
			pBox[i] = '*';
		}
		return pBox;
	}
}

// Takes in a char pointer to first element of box, as well as an int pointer of the box side length
void DisplayBox(const char* pBox, const int* pSideLength)
{
	const int kArrayLength = Square(*pSideLength);// Determine how many elements are needed for array in next line

	// If pBox has been allocated succsefully
	if(!pBox)
	{
		cout << "ERROR: Box does not exist." << endl << "Attempting to skip drawing the box." << endl;
	}
	else
	{
		// Print box to console
		for(int i = 0; i < kArrayLength; ++i)
		{
			cout << pBox[i];
			// Determine when to add a new line as box is stored in a single subscripted array
			if((i+1) % *pSideLength == 0)
			{
				cout << endl;
			}
		}
	}
}

int Square(const int input)
{
	return (input * input);
}

bool CleanUp(char*& pArray)
{
	// Free memory allocated by array
	delete[] pArray;
	// Set pointer to NULL in order to prevent dangling pointers
	pArray = NULL;

	if(pArray)
	{
		return false;
	}
	else
	{
		return true;
	}
}
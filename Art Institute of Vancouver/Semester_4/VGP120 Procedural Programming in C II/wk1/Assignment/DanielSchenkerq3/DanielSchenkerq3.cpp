//-----------------------------
// File:		DanielSchenkerq3.cpp
// Created:		2012/04/07
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>

using namespace std;

//------------FUNCTION PROTOTYPES-------------
int intDivision(const int, const int);									// Returns an int which is the quotient of a dividend being divided by divisor
int intRemainder(const int, const int);									// Returns an int which is the remainder of a dividend being divided by divisor
void numberSpacing(char*&, const int, const int, const int);			// Takes in a char pointer to an array, the size of the array, a number and a space counter, and sets the storage array to a proper format of numbers with spaces inbetween
void numberSpacing(char*&, const int, const int, const int, const int);	// Overloaded function of previous function, that takes in the amount of digits as well, which makes this function slightly faster than the previous
int DigitsInNum(int);													// Returns the amount of digits in a number
int ListSize(const int, const int);										// Returns the size of a list
// Unit tests follow
bool RunAllUnitTests();
bool UnitTestDivision();
bool UnitTestRemainder();
bool UnitTestNumberSpacing();
// Unit tests end
bool CleanUp(char*&);													// Frees allocated memory in the heap by sending a char pointer to the function, and returns whether deallocation was succesful or not

int main()
{
	//initialize random seed
	srand((unsigned)time(NULL));

	//Run unit tests
	if(RunAllUnitTests())
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int intDivision(const int dividend, const int divisor)
{
	int quotient = dividend / divisor;

	return quotient;
}

//This IS negative value safe
int intRemainder(const int dividend, const int divisor)
{
	int remainder = dividend % divisor;

	return remainder;

}

void numberSpacing(char*& storageArray, const int sizeOfArray, const int num, const int spaces)
{
	const int kAmountOfDigits = DigitsInNum(num);// Calculate amount of digits in num and store it into a const int
	char* pStringNum = new (nothrow) char[kAmountOfDigits + 1];// Allocate a single subscripted array to store box data in of length kAmountOfDigits

	// If pStringNum has been allocated succsefully
	if(!pStringNum)
	{
		cout << "ERROR: Unable to allocate memory for array pStringNum." << endl;
		abort();
	}
	// Converts integer into a string, and stores it in target destination pStringNum
	itoa(num,pStringNum,10);

	// Store either a number or a space into the pStringNum array
	for(int i = 0; i < sizeOfArray; ++i)
	{
		if(intRemainder(i, (spaces + 1)) == 0)
		{
			storageArray[i] = pStringNum[intDivision(i, (spaces + 1))];
		}
		else
		{
			storageArray[i] = ' ';
		}
	}
	storageArray[sizeOfArray-1] = '\0';

	CleanUp(pStringNum);
}

// Refer to above function for understanding of code as this is just a overloaded function
void numberSpacing(char*& storageArray, const int sizeOfArray, const int num, const int digitsInNum, const int spaces)
{
	char* pStringNum = new (nothrow) char[digitsInNum];
	if(!pStringNum)
	{
		cout << "ERROR: Unable to allocate memory for array pStringNum." << endl;
		abort();
	}

	itoa(num,pStringNum,10);

	for(int i = 0; i < sizeOfArray; ++i)
	{
		if(intRemainder(i, (spaces + 1)) == 0)
		{
			storageArray[i] = pStringNum[intDivision(i, (spaces + 1))];
		}
		else
		{
			storageArray[i] = ' ';
		}
	}
	storageArray[sizeOfArray-1] = '\0';

	CleanUp(pStringNum);
}

int DigitsInNum(int num)
{
	int digits = 0;
	while(num > 0)
	{
		num /= 10;
		++digits;
	}

	return digits;
}

int ListSize(const int num, const int spaces)
{
	int amountOfDigits = DigitsInNum(num);

	/*eg a 4 digit number with 2 spaces after each number:
	treat a digit as an additional character with each group of spaces,
	so that we can multiply amount of digits times characters
	4 * (2 + 1) = 12 slots
	however with this we'll have the amount of spaces after a digit extra so we need to subtract that
	12 - spaces
	= 12 - 2
	= 10
	while adding 1 slot to account for null terminator,
	= 10 + 1
	= 11
	*/
	return (amountOfDigits * (spaces + 1)) - spaces + 1;
}

bool RunAllUnitTests()
{
	bool successful = true;

	if(!UnitTestDivision())
	{
		successful = false;
		cout << "UnitTestDivision() unsuccessful." << endl;
	}
	cout << endl;
	if(!UnitTestRemainder())
	{
		successful = false;
		cout << "UnitTestRemainder() unsuccessful." << endl;
	}
	cout << endl;
	if(!UnitTestNumberSpacing())
	{
		successful = false;
		cout << "UnitTestNumberSpacing() unsuccessful." << endl;
	}
	cout << endl;
	
	if(successful)
	{
		cout << "All tests succesful." << endl;
	}

	return successful;
}

bool UnitTestDivision()
{
	int dividend;
	int divisor = 0;
	int quotient;

	cout << "Enter dividend value:" << endl;
	cin >> dividend;

	while(divisor == 0)
	{
		cout << "Enter divisor value:" << endl;
		cin >> divisor;
		if(divisor == 0)
		{
			cout << "Can not divide by 0." << endl;
		}
	}
	
	quotient = intDivision(dividend, divisor);

	cout << dividend << " / " << divisor << " = " << quotient << "." << endl;

	return true;

}

bool UnitTestRemainder()
{
	int dividend;
	int divisor = 0;
	int remainder;

	cout << "Enter dividend value:" << endl;
	cin >> dividend;

	while(divisor == 0)
	{
		cout << "Enter divisor value:" << endl;
		cin >> divisor;
		if(divisor == 0)
		{
			cout << "Can not divide by 0." << endl;
		}
	}

	remainder = intRemainder(dividend, divisor);

	cout << "The remainder of " << dividend << " / " << divisor << " is " << remainder << "." << endl;

	return true;
}

bool UnitTestNumberSpacing()
{
	//pick a random number
	const int kOffset = 1;
	const int kMax = 32767;
	const int randomNum =  rand() % kMax + kOffset;

	//determine spaces inbetween numbers
	int spaces = -1;
	while(spaces < 0)
	{
		cout << "How many spaces would you like inbetween each number?" << endl;
		cin >> spaces;
		if(spaces < 0)
		{
			cout << "The spaces value must be at least 0." << endl;
		}
	}

	//determine array size required and allocate accordingly
	const int kSizeOfList = ListSize(randomNum, spaces);
	char* pNumWithSpaces = new (nothrow) char[kSizeOfList];
	if(!pNumWithSpaces)
	{
		cout << "ERROR: Unable to allocate memory for array pNumWithSpaces." << endl;
		abort();
	}

	numberSpacing(pNumWithSpaces, kSizeOfList, randomNum, spaces);

	cout << "The number " << randomNum << " with " << spaces << " space(s) inbetween each number is: ";
	for(int i = 0; pNumWithSpaces[i] != NULL; ++i)
	{
		cout << pNumWithSpaces[i];
	}
	cout << "." << endl;

	CleanUp(pNumWithSpaces);

	return true;
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
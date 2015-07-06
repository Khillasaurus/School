//=============================================================================
// File:		r8randomgeneration.cpp
// Date:		2012/08/17
// Copyright:	Daniel Schenker
// Description:	Defines the entry point for the console application.
//=============================================================================

//=============================================================================
// Includes
//=============================================================================

#include "stdafx.h"

//=============================================================================
// Function Prototypes
//=============================================================================

void intToBinary(int number, unsigned char* pDestination);
const void printArray(unsigned char* pArray, int arrayLength) ;

//=============================================================================
// Main
//=============================================================================

int _tmain(int argc, _TCHAR* argv[])
{
	//Seed
	int seed = 9;
	const int kBinaryBuffLength = 8;
	unsigned char binaryNum[kBinaryBuffLength];
	unsigned char* pBinaryNum = &binaryNum[0];

	intToBinary(seed, pBinaryNum);

	printArray(pBinaryNum, kBinaryBuffLength);

	return 0;
}

//=============================================================================
// Functions
//=============================================================================

void intToBinary(int number, unsigned char* pDestination)
{
	unsigned char* pTemp = pDestination;

	int remainder;

	if(number <= 1)
	{
		*pTemp = number;
		++pTemp;
		return;
	}

	remainder = number % 2;
	intToBinary(number >> 1, pTemp);

	*pTemp = remainder;
	++pTemp;
}

void binary(int number, unsigned char* pDestination)
{
	unsigned char* pTemp = pDestination;

	int remainder;

	if(number <= 1)
	{
		cout << number;
		return;
	}

	remainder = number%2;
	binary(number >> 1);    
	cout << remainder;
}

//-----------------------------------------------------------------------------

const void printArray(unsigned char* pArray, int arrayLength)
{
	unsigned char* pTemp = pArray;
	for(int i = 0; i < arrayLength; ++i)
	{
		printf("%u ", *pTemp);
		++pTemp;
	}
	printf("\n");
}

//-----------------------------------------------------------------------------
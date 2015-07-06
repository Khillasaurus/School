//----------------------------------
// File:		DanielSchenkerq4.cpp
// Created:		2012/04/18
// Copyright:	Daniel Schenker
//----------------------------------

#include "stdio.h"

//------------FUNCTION PROTOTYPES-------------
unsigned int GetUnsignedBase10Number();//Returns: a base 10 integer
void ConvertToBinary(unsigned int);//Takes in: base 10 number needing to be converted to binary
unsigned int Power2(unsigned int, unsigned int);//Takes in: a positive base 10 number

int main()
{
	printf("Enter the number that you would like converted into binary.\n");
	unsigned int number = GetUnsignedBase10Number();
	unsigned int changedNumber = number;
	printf("Enter the number that you would to be the exponent in the latter calculations.\n");
	unsigned int pow = GetUnsignedBase10Number();

	printf("Before making changes to the number %d.\n", number);
	printf("Showing all 32 bits:\n");
	printf("In binary: ");
	ConvertToBinary(number);
	printf("\n");

	printf("After making changes to the number %d.\n", changedNumber);
	changedNumber = Power2(changedNumber, pow);
	printf("Showing all 32 bits:\n");
	printf("In Decimal: %d\nIn binary: ", changedNumber);
	ConvertToBinary(changedNumber);
	printf("\n");

	return 0;
}

unsigned int GetUnsignedBase10Number()
{
	int number = -1;

	while(number < 0)
	{
		printf("Enter a positive number:\n");
		scanf("%d", &number);
		if(number < 0)
		{
			printf("The value you enter must be positive.\n");
		}
	}
	
	return ((unsigned int)number);
}

void ConvertToBinary(unsigned int decimal)
{
	const int kBitsInByte = 8;
	const int kBits = (sizeof(int) * kBitsInByte);

	for(int i = (kBits - 1); i >= 0; --i)
	{
		//Bit Masking
		if(decimal & (1 << i))
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
		//Formatting: adding a space every 4 bits for clarity
		if(i % 4 == 0)
		{
			printf(" ");
		}
	}
}

unsigned int Power2(unsigned int number, unsigned int pow)
{
	return number * (2 << (pow - 1));
}
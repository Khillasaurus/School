//----------------------------------
// File:		DanielSchenkerq2.cpp
// Created:		2012/04/18
// Copyright:	Daniel Schenker
//----------------------------------

#include "stdio.h"

//------------FUNCTION PROTOTYPES-------------
int GetBase10Number();//Returns: a base 10 integer
void ConvertToBinary(int);//Takes in: base 10 number needing to be converted to binary

int main()
{
	int number = GetBase10Number();

	printf("Showing all 32 bits:\n");
	ConvertToBinary(number);
	
	printf("\n");

	return 0;
}

int GetBase10Number()
{
	int number = 0;

	printf("Enter the number that you would like converted into binary.\n");
	scanf("%d", &number);
	
	return number;
}

//store into array instead of simply printing
//then countdown using a for loop until i find first 1 (non zero)
//then allocate an array of i size
//copy contents into 

//nvm better idea:
//printf until i hit first print 1 (not 0)
//then multiply by (10^bit place)
//now you have a new int which represents the number in binary
//this way i can also store both full 31 and minimum required bits into a char array

void ConvertToBinary(int decimal)
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
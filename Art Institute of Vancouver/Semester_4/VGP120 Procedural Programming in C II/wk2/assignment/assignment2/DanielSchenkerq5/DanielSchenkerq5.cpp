//----------------------------------
// File:		DanielSchenkerq5.cpp
// Created:		2012/04/18
// Copyright:	Daniel Schenker
//----------------------------------

#include "stdio.h"

//------------FUNCTION PROTOTYPES-------------
void ConvertToBinary(int);//Takes in: base 10 number needing to be converted to binary
unsigned int packCharacters(char, char);

int main()
{
	char first = 0;
	char second = 0;
	unsigned int packed = 0;

	printf("Please enter the value of character one:\n");
	first = getchar();
	printf("Please enter the value of character two:\n");
	fflush(stdin);
	second = getchar();
	
	printf("The 2 characters in binary form before packing:\n");
	printf("Character One: ");
	ConvertToBinary((int)first);
	printf("\n");
	printf("Character Two: ");
	ConvertToBinary((int)second);
	printf("\n");

	printf("Packing the two characters into an unsigned integer variable...\n");
	packed = packCharacters(first, second);

	printf("The 2 characters in packed form of the characters in binary:\n");
	ConvertToBinary(packed);
	printf("\n");

	printf("\n");


	return 0;
}

void ConvertToBinary(int decimal)
{
	const int kBitsInByte = 8;
	int bits = (sizeof(int) * kBitsInByte);

	for(int i = (bits - 1); i >= 0; --i)
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

unsigned int packCharacters(char first, char second)
{
	unsigned int packed = first;
	packed = packed << 8;

	return packed;
}
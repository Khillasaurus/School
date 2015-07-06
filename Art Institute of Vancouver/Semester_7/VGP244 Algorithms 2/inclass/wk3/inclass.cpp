//=================================================================================================
// File Name:		inclass.cpp
// Created by:		Daniel Schenker
// Data Created:	2013/01/21
// Data Modified:	2013/01/21
// Descriptions:	Defines the entry point for the console application.
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Pre-Compiled Headers
#include "stdafx.h"

//File Input/Output
#include <cstdio>

//=================================================================================================
// Function Prototypes
//=================================================================================================

unsigned int* CreateFreqTable(const char& inputFileName);
void PrintFreqTable();

//=================================================================================================
// Main
//=================================================================================================

int _tmain(int argc, _TCHAR* argv[])
{
	// huffman compression

	 // char buff[...] = "aaaabbbc"

	//1 build a frequency table
	 //	amount of times each character/octet/word/compression ccurs in data stream
	
	 // 'a' == 4
	 // 'b' == 3
	 // 'c' == 1

	//2 assign codes to each entry
	 //	stored in a tree	(priority queue)

	//3 compressed output phase
	 //	header (should be alligned)
	 //	a)		entry count in table
	 //	a)		code to character (or whatever) lookup table
	 //	or b)	offset to data
	 //	data

	//4 input phase
	 //		read the data, and for each bit sequence
	 //		look up the code,
	 //		find the character
	//		write out the decompressed data

	/*
	if( Encode( "a3 - data.txt", "a3 - data.bin" ) )
	{
		Decode( "a3 - data.bin", "a3 - decoded.txt" );
	}
	*/

	//temp
	const char* inputFileName = new char[256];
	inputFileName = "input.txt";
	//const char* outputFileName = new char[256];
	//outputFileName = "output.txt";

	CreateFreqTable(*inputFileName);

	if(inputFileName)
	{
		delete[] inputFileName;
	}
	//if(outputFileName)
	//{
	//	delete[] outputFileName;
	//}


	return 0;
}

//=================================================================================================
// Functions
//=================================================================================================

unsigned int* CreateFreqTable(const char& inputFileName)
{
	//Create frequency table
	unsigned int freqTable[256];

	//Create file pointer
	FILE* fIn;

	//Open file for reading in binary
	fopen_s(&fIn, &inputFileName, "rb");
	if(fIn != NULL)
	{
		//Calculate file size
		fseek(fIn, 0, SEEK_END);
		long fileSize = ftell(fIn);

		//Set file pointer back to the beginning of the file
		fseek(fIn, 0, SEEK_SET);

		//Set all occurences before reading file to 0
		for(unsigned int i = 0; i < 256; ++i)
		{
			freqTable[i] = 0;
		}

		//Read file data and store amount of times each character appears
		for(int i = 0; i < fileSize; ++i)
		{
			//++freqTable[static_cast<int>(fscanf_s(fIn, "%c"))];
			++freqTable[static_cast<int>(fgetc(fIn))];
		}
	}
	else
	{
		printf("ERROR: Unable to open file: %s - unsigned int* CreateFreqTable(const char& inputFileName)\n", &inputFileName);
	}

	//temp: print freq table
	for(unsigned int i = 0; i < 256; ++i)
	{
		printf("%u: %u\n", i, freqTable[i]);
	}

	//Sort table from least to greatest occurence count (or vice versa)

	return &freqTable[0];
}

void PrintFreqTable()
{
}

//build tree
//priority_queue<cNode, vector<cNode>, greater<cNode> > q;

/*
public:
	char mValue;
	int mWeight;
	cNode* mChild
*/
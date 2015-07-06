//-----------------------------
// File:		DanielSchenkerq4.cpp
// Created:		2012/04/09
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>

using namespace std;

//------------FUNCTION PROTOTYPES-------------
// Unit tests
void DoUsingManyFunctions(int*&, const int, const int);
void DoMoreEfficiently(int*&, const int, const int);
// Unit tests end
int RandomNum(const int);										// Returns a random number rolled from passing in a dice type
int RandomNum(const int, const int);							// Returns a random number by passing in a maximum difference and an offset
int Sum(const int, const int);									// Returns the sum of two integers
void DisplayResults(const int* const, const int, const int);	// Takes in a storage array, array size, and amount of tests, followed by displaying results
bool ResetArray(int*&, const int);								// Resets target array of array size to have every element equal 0 and returns whether succesful or not

int main()
{
	//initialize random seed
	srand((unsigned)time(NULL));

	const int kPossibleOutcomes = 11;// Possible number of outcomes of the sum of two d6 dice added
	int tally[kPossibleOutcomes] = {0};// Storage array to tally results
	int* pTally = &tally[0];// Pointer to storage array
	const int kTries = 36000;// Amount of tests to perform

	cout << "Perfom task in inefficient but more intuitive method." << endl;
	DoUsingManyFunctions(pTally, kPossibleOutcomes, kTries);

	// Test to see if array could be reset
	if(!ResetArray(pTally, kPossibleOutcomes))
	{
		cout << "ERROR: Could not reset array. Ending main function of \"DanielSchenkerq4.cpp\" ." << endl;
		return 1;
	}
	cout << endl;

	cout << "Perfom task with relatively better performance, but is more difficult to follow code." << endl;
	DoMoreEfficiently(pTally, kPossibleOutcomes, kTries);

	return 0;
}

void DoUsingManyFunctions(int*& pTally, const int kArraySize, const int kTries)
{
	//nameing random numbers d6, as that is the phonetical way of calling a dice with 6 sides counting from 1 to 6
	int d6a;
	int d6b;
	int sumOfDice;

	// Run test Ktries amount of times
	for(int i = 0; i < kTries; ++i)
	{
		d6a = RandomNum(6);
		d6b = RandomNum(6);
		sumOfDice = Sum(d6a, d6b);
		++pTally[sumOfDice - 2];
	}
	DisplayResults(pTally, kArraySize, kTries);

}

void DoMoreEfficiently(int*& pTally, const int kArraySize, const int kTries)
{
	/*
	the math inside this for loop can be simplified even further many different ways,
	but all of those methods lead to weird math that doesn't make much sense at all,
	and only nets in a very tiny performance gain,
	hence the name of the function containing the word "More", not "Most"
	*/
	// Run test Ktries amount of times
	for(int i = 0; i < kTries; ++i)
	{
		++pTally[( (rand() % 6 + 1) + (rand() % 6 + 1) ) - 2];
	}
	DisplayResults(pTally, kArraySize, kTries);

}

int RandomNum(const int basicDiceType)
{
	return rand() % basicDiceType + 1;
}

int RandomNum(const int max, const int offset)
{
	return rand() % max + offset;
}

int Sum(const int a, const int b)
{
	return a + b;
}

// Display results with 4 different pieces of data: Value, Times Rolled, % of Total Rolls, Bar Graph
void DisplayResults(const int* const pTally, const int kArraySize, const int kTries)
{
	int percentage;

	cout << "Times each amount rolled out of " << kTries << " tries:" << endl;
	cout << "Value\tTimes Rolled\t% of Total Rolls\tBar Graph" << endl;
	for(int i = 0; i < kArraySize; ++i)
	{
		percentage = ( (float)(100 * ((float)pTally[i] / (float)kTries)) );
		cout << i + 2 << ")\t" << pTally[i] << "\t\t" << percentage << "%\t\t\t";
		for(int i = 0; i < percentage; ++i)
		{
			cout << "|";
		}
		cout << endl;
	}
}

bool ResetArray(int*& pArray, const int kArraySize)
{
	if(pArray)
	{
		for(int i = 0; i < kArraySize; ++i)
		{
			pArray[i] = 0;
		}
		return true;
	}
	return false;
}
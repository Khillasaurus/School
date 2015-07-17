#include <stdlib.h>
#include <iostream>

using namespace std;

// function prototypes
void Insert(int );	// Function to insert “value” into the end of the array, calls Resize() when necessary
void Remove(int );	// Function to remove “value” from the array
void Resize();	// Function to resize the array to “newCapacity”
void Print();		// Function to print the contents of the array, including its size/capacity

// global variables
int* gArray = NULL;
int gSize = 0;		// Number of elements currently in the array
int gCapacity = 0;	// Maximum capacity of the array


int main()
{
	gArray = new int[gCapacity];

	int choice = 0;
	int number;

	while ( choice != 3 )
	{
		cout << "What do you want to do?" << endl;
		cout << "1. Insert" << endl;
		cout << "2. Remove" << endl;
		cout << "3. Quit" << endl;
		cout << "Your choice: ";
		cin >> choice;
		cout << endl;

		while ( choice < 1 || choice > 3 )
		{
			cout << "You have entered an invalid input." << endl;
			cout << "What do you want to do?" << endl;
			cout << "1. Insert" << endl;
			cout << "2. Remove" << endl;
			cout << "3. Quit" << endl;
			cout << "Your choice: ";
			cin >> choice;
			cout << endl;
		}

		if ( choice == 1 )
		{
			cout << "Enter a number: ";
			cin >> number;

			Insert(number);
			Print();
		}

		else if ( choice == 2 )
		{
			cout << "Enter a number: ";
			cin >> number;

			Remove(number);
			Print();
		}

	}

	//delete[] gArray;

	cout << "KThxBye!!!" << endl;

	return 0;
}


void Insert(int value)
{
	if ( gSize == gCapacity )
	{
		Resize();
	}
	gArray[gSize] = value;
	++gSize;
}


void Remove(int value)
{
	bool foundNumber = false;

	for ( int j = 0; j < gCapacity; ++j )
	{
		if ( value == gArray[j] )
		{
			foundNumber = true;
		}
		if ( foundNumber == true )
		{
			if ( j < gCapacity )
			{
				gArray[j] = gArray[j+1];
			}
		}
	}
	if (foundNumber == true )
	{
		--gSize;
	}
	foundNumber = false;
}


void Resize()
{
	//int* resize_array = new int[gCapacity + 1];
	//for ( int m = 0; m < gCapacity; m++ )
	//{
	//	resize_array[m] = gArray[m];
	//}
	//
	++gCapacity;
	//gArray = resize_array;
	//delete[] resize_array;
}


void Print()
{
	cout << "Array contains: ";
		for ( int i = 0; i < gSize; ++i )
		{
			if (i != gSize - 1 )
			{
				cout << gArray[i] << ", ";
			}
			else
			{
				cout << gArray[i];
			}
		}
	cout << " (size = " << gSize << ", capacity = " << gCapacity << ")" << endl << endl;

}
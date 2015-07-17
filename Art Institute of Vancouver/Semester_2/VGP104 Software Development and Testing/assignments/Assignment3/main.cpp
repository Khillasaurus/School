#include <stdlib.h>
#include <iostream>

int GetNumEvens(const int*, int);
int GetNumGreaterThanTen(const int*, int);
int GetNumPowersOfTwo(const int*, int);
int GetNumPrimes(const int*, int);

using namespace std;

int main()
{
	int inputNum = 0;
	const int size = 100;
	int list[size];
	int* listPtr = list;
	int evens = 0;
	int greaterThan10 = 0;
	int powersOf2 = 0;
	int primes = 0;

	cout << "=== Histogram ===" << endl;
	cout << " Please enter the number of data entries: ";
	cin >> inputNum;

	for ( int i = 0; i < inputNum; ++i )
	{
		cout << "Entry[" << i << "] = ";
		cin >> list[i];
	}

	cout << "The entries are:";
	for (int j = 0; j < inputNum; ++j )
	{
		cout << " " << list[j];
	}
	cout << endl << endl;

	evens			= GetNumEvens( listPtr, inputNum );
	greaterThan10	= GetNumGreaterThanTen( listPtr, inputNum );
	powersOf2		= GetNumPowersOfTwo( listPtr, inputNum );
	primes			= GetNumPrimes( listPtr, inputNum );

	cout << "=== Results ===" << endl;
	cout << "Evens: ";
	for (int k1 = 0; k1 < evens; ++k1 )
	{
		cout << "*";
	}
	cout << endl;
	cout << "Greater Than 10: ";
	for (int k2 = 0; k2 < greaterThan10; ++k2 )
	{
		cout << "*";
	}
	cout << endl;
	cout << "Powers Of 2: ";
	for (int k3 = 0; k3 < powersOf2; ++k3 )
	{
		cout << "*";
	}
	cout << endl;
	cout << "Primes: ";
	for (int k4 = 0; k4 < primes; ++k4 )
	{
		cout << "*";
	}
	cout << endl << "KThxBye!!!" << endl;

    return 0;
}

int GetNumEvens(const int* listPtr, int size)
{
	int result = 0;
	for ( int i = 0; i < size; ++i )
	{
		if ( *listPtr%2 == 0 )
		{
			++result;
		}
		++listPtr;
	}
	return result;
}

int GetNumGreaterThanTen(const int* listPtr, int size)
{
	int result = 0;
	for ( int i = 0; i < size; ++i )
	{
		if ( *listPtr > 10 )
		{
			++result;
		}
		++listPtr;
	}
	return result;
}

int GetNumPowersOfTwo(const int* listPtr, int size)
{
	int result = 0;
	int storage = 0;
	for ( int i = 0; i < size; ++i )
	{
		storage = *listPtr;
		while ( storage >= 2 )
		{
			if ( storage % 2 != 0 )
			{
				storage = 1;
			}
			if ( storage == 2 )
			{
				++result;
			}
			storage /= 2;
		}
		++listPtr;
	}
	return result;
}

int GetNumPrimes(const int* listPtr, int size)
{
	int result = 0;
	int isPrime = 1;
	int j = 2;
	for ( int i = 0; i < size; ++i )
	{
		if ( (*listPtr == 1) || (*listPtr == 2) )
		{
			++result;
			j = (*listPtr)+1;//exit for j loop
		}
		for( j = 2; j < *listPtr; ++j )
		{
			isPrime = *listPtr % j;
			if ( isPrime == 0 )
			{
				j = (*listPtr)+1;//exit for j loop
			}
			else if ( j == ((*listPtr)-1) )
			{
				++result;
			}
		}
		++listPtr;
	}
	return result;
}

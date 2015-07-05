#include <iostream>

using namespace std;

int exponent( int, int );

int main()
{

	int number;
	int power; 
	int result; 

	cout << "Enter Base Number: ";
	cin >> number;
	cout << "Enter the Power: ";
	cin >> power;

	result = exponent( number, power );

	cout << result << endl;

	return 0;
}

int exponent( int number, int power )
{
	if( power == 1 )
	{
		return number;
	}
	else
	{
		return ( number*exponent(number,power-1) );
	}
}

	
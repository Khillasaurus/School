// Created by: Daniel Schenker
// Last edited: 2011/10/22

#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

//function prototypes
int isInteger(char []);

int main ()
{
	int guess;
	int number;

	//initialize random seed:
	srand (time(NULL));

	//generate secret number:
	number = rand() % 100 + 1;

	cout << "Guess a number between 1 and 100 inclusive!\n";
	cout << "I'll tell you if it's too high or too low until you guess it.\n";

	char buffer[20];
	cin >> buffer;

	guess = isInteger(buffer);
	while (guess == -97612)//while guess is not an integer ask for a new number
	{
		cout << "You have entered an invalid input." << endl;
		cout << "Please guess a new number between 1 and 100 inclusive." << endl;
		cin >> buffer;
		guess = isInteger(buffer);
	}

	do
	{
		while (guess < 1 || guess > 100)
		{
			if (guess < 1)
			{
				cout << "The number you have entered is to low. Please guess a new number between 1 and 100 inclusive." << endl;
				cin >> buffer;
				guess = isInteger(buffer);
				while (guess == -97612)//while guess is not an integer ask for a new number
				{
					cout << "You have entered an invalid input." << endl;
					cout << "Please guess a new number between 1 and 100 inclusive." << endl;
					cin >> buffer;
					guess = isInteger(buffer);
				}
			}
			else if (guess > 100)
			{
				cout << "The number you have entered is to high. Please guess a new number between 1 and 100 inclusive." << endl;
				cin >> buffer;
				guess = isInteger(buffer);
				while (guess == -97612)//while guess is not an integer ask for a new number
				{
					cout << "You have entered an invalid input." << endl;
					cout << "Please guess a new number between 1 and 100 inclusive." << endl;
					cin >> buffer;
					guess = isInteger(buffer);
				}
			}
		}

		cout << endl;
		if (guess < number)
		{
			cout << "Too Low! Try again!\n" << endl;
			cin >> buffer;
			guess = isInteger(buffer);
			while (guess == -97612)//while guess is not an integer ask for a new number
			{
				cout << "You have entered an invalid input." << endl;
				cout << "Please guess a new number between 1 and 100 inclusive." << endl;
				cin >> buffer;
				guess = isInteger(buffer);
			}
		}
		else if (guess > number)
		{
			cout << "Too High! Try again!\n" << endl;
			cin >> buffer;
			guess = isInteger(buffer);
			while (guess == -97612)//while guess is not an integer ask for a new number
			{
				cout << "You have entered an invalid input." << endl;
				cout << "Please guess a new number between 1 and 100 inclusive." << endl;
				cin >> buffer;
				guess = isInteger(buffer);
			}
		}
	} while (number != guess);

  cout << "Wow you got it!!!\nKThxBye!!!\n" << endl;

  return 0;
}

 
int isInteger(char buffer[])
{

	//check whether integer or not
	int count = 0;
	bool invalid = false;

	while (buffer[count] != '\0')//loop until end of string
	{
		if ((buffer[count] < '0') || (buffer[count] > '9'))//if input is invalid
		{
			invalid = true;
			break;
		}
		++count;//next character in string
	}

	if (invalid == false)//if input is an integer
	{
		return atoi(buffer);
	}
	else//if input is not valid
	{
		return -97612;
	}
}
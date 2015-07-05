//-----------------------------
// File:		main.cpp
// Created:		2012/2/10
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "card.h"
#include <list>

//function prototypes
bool WantsToPlay();
bool Initialize();
void ShuffleCards();
void DealCards();
bool GameOver();
void PlayRound();
void CalculateWinner();
bool FreeMemory();

// -------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	bool runGame = true;

	while(runGame)
	{
		if(WantsToPlay())
		{
			if(Initialize())
			{
				while(!GameOver())
				{
					PlayRound();
				}
				CalculateWinner();

				if(!FreeMemory())
				{
					cout << "ERROR: Memory could not be freed." << endl;
					break;
				}
			}
			else
			{
				cout << "ERROR: Could not initialize game." << endl;
				break;
			}
		}
		else
		{
			runGame = false;
			cout << "See you next time!" << endl;
		}
	}

	return 0;
}




bool WantsToPlay()
{
	int wantsToPlay = -1;

	while(wantsToPlay < 0 || wantsToPlay > 1)
	{
		cout << "Do you want to play a card game of War?" << endl;
		cout << "Enter 1 for yes or 0 for no." << endl;
		cin >> wantsToPlay;
		if(wantsToPlay < 0 || wantsToPlay > 1)
		{
			cout << "You have entered an incorrect value." << endl;
		}
	}
	if(wantsToPlay == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}




bool Initialize()
{
	//NOT DONE YET!
	//allocate cards here

	std::list<int> myList;
	std::list<int>::iterator it;

	myList.insert(myList.end(), 1);
	myList.insert(myList.end(), 5);
	myList.insert(myList.end(), 3);
	myList.insert(myList.end(), 6);

	cout << "Unsorted" << endl;
	for(it = myList.begin(); it !=myList.end(); ++it)
	{
		cout << "value = " << (*it) << endl;
	}

	cout << "Sorted" << endl;
	myList.sort();
	for(it = myList.begin(); it !=myList.end(); ++it)
	{
		cout << "value = " << (*it) << endl;
	}

	cout << "-- yay --" << endl;


	ShuffleCards();
	DealCards();


	return true;//temporary
}




void ShuffleCards()
{
}




void DealCards()
{
}




bool GameOver()
{
	return true;//temporary
}




void PlayRound()
{
}




void CalculateWinner()
{
}




bool FreeMemory()
{
	return true;//temporary
}
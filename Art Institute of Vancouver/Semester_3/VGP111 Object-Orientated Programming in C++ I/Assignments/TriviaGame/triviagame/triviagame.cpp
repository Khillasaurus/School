//-----------------------------
// File:		triviagame.cpp
// Created:		2012/3/14
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "game.h"
#include "question.h"

//------------FUNCTION PROTOTYPES-------------
bool WantsToPlay();

//-----------MAIN ENTRY TO PROGRAM------------

int _tmain(int argc, _TCHAR* argv[])
{
	bool isPlaying = WantsToPlay();
	while(isPlaying)
	{
		//Create Game
		cGame* pMyGame = new cGame(true);

		//Initialize Game
		pMyGame->InitializeGame();
		
		//Play Until No Questions Are Left
		for(Uint32 questionCounter = 0; pMyGame->getGameState(); ++questionCounter)
		{
			Uint32 pointsChange;
			//Check To See If Any Questions Are Left
			if(questionCounter == cGame::sQuestionTotal)
			{
				pMyGame->setGameState(false);
				break;
			}
			//Play A Round
			if(pMyGame->QuizOnce(questionCounter))//Add Points
			{
				pointsChange = 5;
				//Use operator overloading for += here instead if possible
				pMyGame->setPlayerScore(pointsChange, true, true);
			}
			else//Remove Points
			{
				pointsChange = 3;
				//Use operator overloading for += here instead if possible
				pMyGame->setPlayerScore(pointsChange, false, true);
			}
			pMyGame->DisplayScore();
		}
		//Free Memory
		delete pMyGame;
		pMyGame = NULL;

		//Ask If User Would Like To Play Again
		isPlaying = WantsToPlay();
	}

	return 0;
}

//--------------OTHER FUNCTIONS---------------

bool WantsToPlay()
{
	bool state = false;
	char input = '0';

	cout << "Would you like to play a game of Gaming Trivia?" << endl;
	cout << "y for yes, n for no." << endl;
	while(input != 'y' || input != 'n')
	{
		cin >> input;
		if(input == 'n')
		{
			input = 'N';
		}
		else if(input == 'y')
		{
			input = 'Y';
		}
		if(input == 'N' || input == 'Y')
		{
			break;
		}
		else
		{
			cout << "You have entered an invalid answer." << endl;
			cout << "Would you like to play a game of Trivia?" << endl;
			cout << "y for yes, n for no." << endl;
		}
	}

	if (input == 'Y')
	{
		state = true;
	}
	else
	{
		state = false;
	}

	return state;
}
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
		cGame myGame = new cGame(true);
		cGame* pMyGame = &myGame;

		//Initialize Game
		myGame.InitializeGame();
		
		//Play Until No Questions Are Left
		for(Uint32 questionCounter = 0; myGame.getGameState(); ++questionCounter)
		{
			//Check To See If Any Questions Are Left
			if(questionCounter == cGame::sQuestionTotal)
			{
				myGame.setGameState(false);
				break;
			}
			//Play A Round
			if(myGame.QuizOnce(questionCounter))//Add Points
			{
				Uint32 pointsEarned = 5;
				//Use operator overloading for += here instead if possible
				myGame.setPlayerScore(myGame.getPlayerScore() + pointsEarned);
			}
			else//Remove Points
			{
				Uint32 pointsLost = 3;
				//Use operator overloading for += here instead if possible
				myGame.setPlayerScore(myGame.getPlayerScore() - pointsLost);
			}
		}
		//Free Memory
		delete pMyGame;

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
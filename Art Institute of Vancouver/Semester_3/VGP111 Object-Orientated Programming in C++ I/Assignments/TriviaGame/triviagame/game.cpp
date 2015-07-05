//-----------------------------
// File:		game.cpp
// Created:		2012/3/14
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "game.h"
#include "question.h"

const Uint32 cGame::sQuestionTotal = 9;

//----------SPECIAL MEMBER FUNCTIONS----------

cGame::cGame()
{
}

cGame::cGame(bool state)
:	mPlayerScore(0)
{
	setGameState(state);
}

cGame::~cGame()
{
}

//----------PRIVATE FUNCTIONS-----------------

void cGame::InitQuestions()
{
	const char *kFileName = "database.txt";
	const Uint32 kDataPieces = 6;
	for(int questionNum = 0; questionNum < kAmountOfQuestions; ++questionNum)
	{
		cQuestion *pQuestion = new cQuestion();

		pQuestion->mQuestion = readStringFromFile(kFileName, questionNum, kDataPieces, 0);
		pQuestion->mAnswer1 = readStringFromFile(kFileName, questionNum, kDataPieces, 1);
		pQuestion->mAnswer2 = readStringFromFile(kFileName, questionNum, kDataPieces, 2);
		pQuestion->mAnswer3 = readStringFromFile(kFileName, questionNum, kDataPieces, 3);
		pQuestion->mAnswer4 = readStringFromFile(kFileName, questionNum, kDataPieces, 4);
		pQuestion->mCorrectAnswer = readNumberFromFile(kFileName, questionNum, kDataPieces, 5);

		mList.push_back( pQuestion );
	}
}

void cGame::Shuffle()
{
	random_shuffle(mList.begin(), mList.end());
}

bool cGame::IsCorrectString(Uint32 questionNumber, string userChoice)
{
	Uint32 correctNumber = mList[questionNumber]->getCorrect();
	string answer;

	if(correctNumber == 1)
	{
		answer = mList[questionNumber]->getAnswer1();
		if(answer.compare(userChoice) == 0)
		{
			cout << "Congradulations! You are correct!" << endl;
			return true;
		}
		else
		{
			cout << "Sorry, wrong answer." << endl;
			cout << "The correct answer is: " << correctNumber << " - ";
			 cout << mList[questionNumber]->getAnswer1() << endl;
			return false;
		}
	}
	else if(correctNumber == 2)
	{
		answer = mList[questionNumber]->getAnswer2();
		if(answer.compare(userChoice) == 0)
		{
			cout << "Congradulations! You are correct!" << endl;
			return true;
		}
		else
		{
			cout << "Sorry, wrong answer." << endl;
			cout << "The correct answer is: " << correctNumber << " - ";
			 cout << mList[questionNumber]->getAnswer2() << endl;
			return false;
		}
	}
	else if(correctNumber == 3)
	{
		answer = mList[questionNumber]->getAnswer3();
		if(answer.compare(userChoice) == 0)
		{
			cout << "Congradulations! You are correct!" << endl;
			return true;
		}
		else
		{
			cout << "Sorry, wrong answer." << endl;
			cout << "The correct answer is: " << correctNumber << " - ";
			cout << mList[questionNumber]->getAnswer3() << endl;
			return false;
		}
	}
	else
	{
		answer = mList[questionNumber]->getAnswer4();
		if(answer.compare(userChoice) == 0)
		{
			cout << "Congradulations! You are correct!" << endl;
			return true;
		}
		else
		{
			cout << "Sorry, wrong answer." << endl;
			cout << "The correct answer is: " << correctNumber << " - ";
			 cout << mList[questionNumber]->getAnswer4() << endl;
			return false;
		}
	}
}

bool cGame::IsCorrectNumber(Uint32 questionNumber, Uint32 userChoice)
{
	Uint32 answer = mList[questionNumber]->getCorrect();
	if(answer == userChoice)
	{
		return true;
	}
	else
	{
		return false;
	}
}

string cGame::readStringFromFile(const char* kFileName, const Uint32 questionNum, const Uint32 kDataPieces, const Uint32 accessModifier)
{
	/*
	If we want to read the 3rd question, and return the 5th piece of data (Answer4 in this case)
	The formula would be:
	read line number	(question number	*	pieces of data	+	line difference	)	=	line number
	which is:			(3					*	6				+	5				)	=	line 23
	where
		question number	=	question number
		pieces of data	=	amount of different pieces of data held in the file, which is determined by the amount of data in a question object that is called in the 2nd constructor function (noted in the list below)
		line difference	=	which piece of data is needed which is determined by the order of data in a question object that is called in the 2nd constructor function (noted in the list below)
			0: question
			1: answer 1
			2: answer 2
			3: answer 3
			4: answer 4
			5: correct answer
	*/

	Uint32 lineno = (questionNum * kDataPieces) + accessModifier;
	string line;

	ifstream dataFile (kFileName);
	if(dataFile.is_open())
	{
		for(Uint32 currentLine = 0; (currentLine < lineno) && (!dataFile.eof()); ++currentLine)
		{
			getline (dataFile, line);
		}
		getline (dataFile, line);
		dataFile.close();
	}
	else
	{
		cout << "ERROR: Could not load database file!!!" << endl;
	}

	return line;
}

Uint32 cGame::readNumberFromFile(const char kFileName[], const Uint32 questionNum, const Uint32 kDataPieces, const Uint32 accessModifier)
{
	//Refer to readStringFromFile function above to understand how to use
	//I plan to combine these two functions by using a templatized function later

	Uint32 lineno = (questionNum * kDataPieces) + accessModifier;
	string line;
	Uint32 number = -1;

	ifstream dataFile (kFileName);
	if(dataFile.is_open())
	{
		for(Uint32 currentLine = 0; (currentLine < lineno) && (!dataFile.eof()); ++currentLine)
		{
			getline (dataFile, line);
		}
		getline (dataFile, line);
		dataFile.close();
	}
	else
	{
		cout << "ERROR: Could not load database file!!!" << endl;
	}
	if(line[0] >= 48 && line[0] <= 57)//checking whether string is a number using ascii table
	{
		number = atoi(line.c_str());
	}

	return number;
}

//----------PUBLIC FUNCTIONS------------------

void cGame::InitializeGame()
{
	//Initialize Questions
	InitQuestions();

	//Shuffle Questions
	///Shuffle();

	//Set Game State To Playing
	if(!getGameState())
	{
		setGameState(true);
	}
}

bool cGame::QuizOnce(const Uint32 questionCounter)
{
	string userAnswer = "-";
	Uint32 number = -1;
	bool isNumber = false;

	cout << "Question " << questionCounter + 1 << ":" << endl;
	cout << mList[questionCounter]->getQuestion() << endl;
	cout << "1: " << mList[questionCounter]->getAnswer1() << endl;
	cout << "2: " << mList[questionCounter]->getAnswer2() << endl;
	cout << "3: " << mList[questionCounter]->getAnswer3() << endl;
	cout << "4: " << mList[questionCounter]->getAnswer4() << endl;
	cout << "Please enter your answer now." << endl;
	do//prevents user from accidentaly entering a key value used just below
	{
		cin >> userAnswer;

		// validate answer
		//	must be 1, 2, 3, or 4  OR  ~ to escape
		if(userAnswer[0] == '-')
		{
			cout << "Invalid input. Please provide a new answer." << endl;
		}
	}while(userAnswer[0] == '-');

	//determine if user entered a string or number
	if(userAnswer.length() && isdigit( userAnswer[0] ) )
	{
		number = atoi( userAnswer.c_str() );
	}
	else
	{
		number = -1;
	}
	if(number != -1)
	{
		isNumber = true;
		return IsCorrectNumber(questionCounter, number);
	}
	else
	{
		isNumber = false;
		//convert answer to all capital letters
		char c;
		for(Uint32 i = 0; i < userAnswer.length(); ++i)
		{
			c = userAnswer.at(i);
			toupper(c);
		}
		return IsCorrectString(questionCounter, userAnswer);
	}
}

void cGame::DisplayScore()
{
	cout << "Player Score: " << getPlayerScore() << endl;
}

void cGame::ScoreScreen()
{
	Uint32 score = getPlayerScore();

	cout << "You've finished the game!" << endl;
	cout << "Your score is......." << endl << "..." << endl << ". . .... ." << endl << ". ...." << "*ahem*" << endl;
	if(score < 0)
	{
		cout << "Stop messing with the system! At least try..." << endl;
		cout << "Oh as you were wondering, " << score << " points. =P" << endl;
	}
	else if(score < 9)
	{
		cout << score << " points! ...Oh wait, that isn't good..., this isn't gold you know!!!" << endl;
	}
	else if(score < 13)
	{
		cout << score << " points! GG! =)" << endl;
	}
	else if(score < 17)
	{
		cout << score << " points! Great Job!! =)" << endl;
	}
	else if(score < 20)
	{
		cout << score << " points! Congradulations! You're smart!!! =)" << endl;
	}
	else if(score < 22)
	{
		cout << score << " points! Wow you're a genius! Keep up the amazing work!!!! =)" << endl;
	}
	else
	{
		cout << score << " points! Now what did I say about NOT hacking the game to get a perfect score?!!?... ;)" << endl;
	}
	cout << endl << "Thank you for playing!!!" << endl;
	cout << "This game is brought to you by Daniel Schenker! =)" << endl << endl;
}

//------------------SETTERS------------------
void cGame::setGameState(bool state)
{
	mIsRunning = state;
}

void cGame::setPlayerScore(Sint32 num, bool gainOrLoss, bool showChange)
{
	if(showChange)
	{
		cout << "You've ";
		if(gainOrLoss)
		{
			cout << "earned ";
		}
		else
		{
			cout << "lost ";
		}
		cout << num << " points." << endl;
	}
	if(gainOrLoss)
	{
		mPlayerScore += num;
	}
	else
	{
		mPlayerScore -= num;
	}
}

//------------------GETTERS------------------
bool cGame::getGameState() const
{
	return mIsRunning;
}

Sint32 cGame::getPlayerScore() const
{
	return mPlayerScore;
}
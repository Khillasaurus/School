//-----------------------------
// File:		game.cpp
// Created:		2012/3/14
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "game.h"
#include "question.h"

cGame::cGame()
{
}

cGame::cGame(bool state)
:	mPlayerScore(0)
,	mQuestionCounter(0)
{
	mIsRunning = state;
}

cGame::~cGame()
{
}

//-------------------------------------------

void cGame::InitQuestions()
{
	for(int i = 0; i < kAmountOfQuestions; ++i)
	{
		mList.push_back(new cQuestion(i, cGame::mQuestionList[i], cGame::mAnswer1List[i], cGame::mAnswer2List[i], cGame::mAnswer3List[i], cGame::mAnswer4List[i], cGame::mCorrectAnswerList[i]));
	}
}

void cGame::Shuffle()
{
	random_shuffle(mList.begin(), mList.end());
}

bool cGame::isCorrect(Uint32 questionNumber, Uint32 userChoice)
{
	if((*(mList[questionNumber])).getCorrect() == userChoice)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//------------------SETTERS------------------
void cGame::setGameState(bool state)
{
	mIsRunning = state;
}

void cGame::setPlayerScore(Uint32 num)
{
	mPlayerScore = num;
}

void cGame::setQuestionCounter(Uint32 num)
{
	mQuestionCounter = num;
}

void cGame::setQuestionList(string input)
{
	mQuestionList.push_back(input);
}

void cGame::setAnswer1List(string input)
{
	mAnswer1List.push_back(input);
}

void cGame::setAnswer2List(string input)
{
	mAnswer2List.push_back(input);
}

void cGame::setAnswer3List(string input)
{
	mAnswer3List.push_back(input);
}

void cGame::setAnswer4List(string input)
{
	mAnswer4List.push_back(input);
}

void cGame::setCorrectAnswerList(Uint32 input)
{
	mCorrectAnswerList.push_back(input);
}

//------------------GETTERS------------------
bool cGame::getGameState() const
{
	return mIsRunning;
}

Uint32 cGame::getPlayerScore() const
{
	return mPlayerScore;
}

Uint32 cGame::getQuestionCounter() const
{
	return mQuestionCounter;
}
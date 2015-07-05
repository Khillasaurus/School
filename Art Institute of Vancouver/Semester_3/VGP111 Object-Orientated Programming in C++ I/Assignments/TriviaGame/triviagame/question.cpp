//-----------------------------
// File:		question.cpp
// Created:		2012/3/14
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "question.h"

//----------SPECIAL MEMBER FUNCTIONS----------

cQuestion::cQuestion()
{
}

cQuestion::cQuestion(string _mQuestion, string _mAnswer1, string _mAnswer2, string _mAnswer3, string _mAnswer4, Uint32 _mCorrectAnswer)
:	mQuestion(_mQuestion)
,	mAnswer1(_mAnswer1)
,	mAnswer2(_mAnswer2)
,	mAnswer3(_mAnswer3)
,	mAnswer4(_mAnswer4)
,	mCorrectAnswer(_mCorrectAnswer)
{
}

cQuestion::~cQuestion()
{
}

//----------PUBLIC FUNCTIONS------------------

//------------------SETTERS------------------
void cQuestion::setQuestion(string ques)
{
	mQuestion = ques;
}

void cQuestion::setAnswer1(string one)
{
	mAnswer1 = one;
}

void cQuestion::setAnswer2(string two)
{
	mAnswer1 = two;
}

void cQuestion::setAnswer3(string three)
{
	mAnswer1 = three;
}

void cQuestion::setAnswer4(string four)
{
	mAnswer1 = four;
}

void cQuestion::setCorrect(Uint32 answer)
{
	mCorrectAnswer = answer;
}

void cQuestion::setUserString(string choice)
{
	mUserStringAnswer = choice;
}

void cQuestion::setUserNumber(Uint32 choice)
{
	mUserNumberAnswer = choice;
}

//------------------GETTERS------------------
string cQuestion::getQuestion() const
{
	return mQuestion;
}

string cQuestion::getAnswer1() const
{
	return mAnswer1;
}

string cQuestion::getAnswer2() const
{
	return mAnswer2;
}

string cQuestion::getAnswer3() const
{
	return mAnswer3;
}

string cQuestion::getAnswer4() const
{
	return mAnswer4;
}

Uint32 cQuestion::getCorrect() const
{
	return mCorrectAnswer;
}

string cQuestion::getUserString() const
{
	return mUserStringAnswer;
}

Uint32 cQuestion::getUserNumber() const
{
	return mUserNumberAnswer;
}
//-----------------------------
// File:		question.cpp
// Created:		2012/3/14
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "question.h"

cQuestion::cQuestion()
{
}

cQuestion::cQuestion(Uint32 _mQuestionNumber, string _mQuestion, string _mAnswer1, string _mAnswer2, string _mAnswer3, string _mAnswer4, Uint32 _mCorrectAnswer)
:	mQuestionNumber(_mQuestionNumber)
,	mQuestion(_mQuestion)
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

//------------------SETTERS------------------
void cQuestion::setQuestionNumber(Uint32 qNum)
{
	mQuestionNumber = qNum;
}

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

void cQuestion::setUser(Uint32 choice)
{
	mUserAnswer = choice;
}

//------------------GETTERS------------------
Uint32 cQuestion::getQuestionNumber() const
{
	return mQuestionNumber;
}

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

Uint32 cQuestion::getUser() const
{
	return mUserAnswer;
}
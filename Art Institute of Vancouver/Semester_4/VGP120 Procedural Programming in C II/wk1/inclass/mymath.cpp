//-----------------------------
// File:		mymath.cpp
// Created:		2012/04/05
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "mymath.h"

cMyMath::cMyMath()
:	mInput(0)
{
}

cMyMath::~cMyMath()
{
}

int cMyMath::Square(const int input)
{
	return (input*input);
}

void cMyMath::Run()
{
	int x;
	cout << "Enter the number you would like to square." << endl;
	cin >> x;
	cout << "The square of " << x << " is " << Square(x) << "." << endl;
}
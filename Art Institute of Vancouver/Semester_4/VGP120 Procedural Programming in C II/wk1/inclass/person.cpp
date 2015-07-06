//-----------------------------
// File:		person.cpp
// Created:		2012/04/05
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "person.h"

cPerson::cPerson()
:	mAge(0)
,	mHeight(0)
{
}

cPerson::~cPerson()
{
}

void cPerson::Init()
{
	cout << "How old is Daniel in years?" << endl;
	cin >> mAge;
	cout << "How tall is Daniel in cm?" << endl;
	cin >> mHeight;
}

void cPerson::DisplayData()
{
	cout << "Daniel is " << mAge << " years old and " << mHeight << " cm tall." << endl;
}
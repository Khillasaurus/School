//-----------------------------
// File:		inclass.cpp
// Created:		2012/04/05
// Copyright:	Daniel Schenker
//-----------------------------

// inclass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "person.h"
#include "mymath.h"

//function prototypes
void InClassMath();
void InClassPerson();
int Square(const int);

int _tmain(int argc, _TCHAR* argv[])
{
	InClassMath();
	cout << endl;
	InClassPerson();

	return 0;
}

void InClassPerson()
{
	cPerson* pDaniel = new cPerson;
	pDaniel->Init();
	pDaniel->DisplayData();
}

void InClassMath()
{
	cMyMath* pMyCalc = new cMyMath;
	pMyCalc->Run();
}
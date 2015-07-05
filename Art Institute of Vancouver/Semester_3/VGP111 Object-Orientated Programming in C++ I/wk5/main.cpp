//-----------------------------
// File:		main.cpp
// Created:		2012/2/3
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "vgp/vgptime.h"
#include "vgp/vgptimer.h"

//function prototypes

//template<typename T>
//T Add(T a, T b)
//{
//	return a + b;
//}

//template<typename T>
//class cCalculator
//{
//public:
//	T Add(T a, T b)
//	{
//		return a + b;
//	}
//};

extern void LessonWeek5b();

// -------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	cCalculator<int> myCalc;

	int a = myCalc.Add(1, 1);
	int b = myCalc.Sub(1, 1);

	cout << a << endl;
	cout << b << endl;

	cout << endl << endl;

	LessonWeek5b();

	return 0;
}
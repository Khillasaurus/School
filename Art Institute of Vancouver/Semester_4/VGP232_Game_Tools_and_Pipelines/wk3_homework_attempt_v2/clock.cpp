//-----------------------------
// File:		clock.cpp
// Created:		2012/1/26
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "clock.h"

using namespace std;

void cClock::timer()
{

	GetSystemTime(&stStart);

	//daylights saving time checking and time zone adjustment
	bool daylightSavings = true;
	Sint32 daylightSavingsAdjustment;
	if (daylightSavings == true)
	{
		daylightSavingsAdjustment = -7;
	}
	else
	{
		daylightSavingsAdjustment = -8;
	}

	cout << "Date: " << stStart.wYear << "/" << stStart.wMonth << "/" << stStart.wDay << endl;
	cout << "Time: ";
	cout.fill('0');
	cout.width(2);
	cout << stStart.wHour+daylightSavingsAdjustment << "/";
	cout.fill('0');
	cout.width(2);
	cout << stStart.wMinute << "/";
	cout.fill('0');
	cout.width(2);
	cout << stStart.wSecond << "/";
	cout.fill('0');
	cout.width(3);
	cout << stStart.wMilliseconds << endl;

	Uint32 now = stStart.wMinute * 60 * 1000 + stStart.wSecond * 1000 + stStart.wMilliseconds;
	Uint32 stopTime = now + 1000;

	while( now < stopTime )
	{
		GetSystemTime(&stNow);
		
		now = stNow.wMinute * 60 * 1000 + stNow.wSecond * 1000 + stNow.wMilliseconds;
	}
}
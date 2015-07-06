//-----------------------------
// File:		vgptime.cpp
// Created:		2012/1/20
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "vgp/vgptime.h"
#include <windows.h> //for SYSTEMTIME defition
#include <iostream>
//#include <sys/types.h>//necessary?
//#include <sys/timeb.h>//necessary?
using namespace std;

cTime::cTime()
//default constructor
:	mHours(0)
,	mMinutes(0)
,	mSeconds(0)
,	mMilliseconds(0)
{
}

// eg:
// cTime a;
// a.mHour = 5;
// cTime b(a);
// b.mHour == 5;
cTime::cTime(const cTime &rhs)
//default constructor
:	mHours(rhs.mHours)
,	mMinutes(rhs.mMinutes)
,	mSeconds(rhs.mSeconds)
,	mMilliseconds(rhs.mMilliseconds)
{
}

cTime::cTime(const _SYSTEMTIME &st)
:	mHours(st.wHour)
,	mMinutes(st.wMinute)
,	mSeconds(st.wSecond)
,	mMilliseconds(st.wMilliseconds)
{
}

cTime::cTime(Sint32 h, Sint32 m, Sint32 s, Sint32 ms/* = 0*/)
:	mHours(h)
,	mMinutes(m)
,	mSeconds(s)
,	mMilliseconds(ms)
{
}

cTime::cTime(Sint32 _SumMilliseconds)
:	mHours(0)
,	mMinutes(0)
,	mSeconds(0)
,	mMilliseconds(0)
{
	Add(_SumMilliseconds);
}

// assignment operator
// a = b = c;
cTime & cTime::operator =(const cTime &rhs)
{
	mHours = rhs.mHours;
	mMinutes = rhs.mMinutes;
	mSeconds = rhs.mSeconds;
	mMilliseconds = rhs.mMilliseconds;

	return (*this);
}

// subtract
// cTime a( 12, 0, 0 );
// cTime b( 6, 33, 57 );
// cTime c = a - b;
cTime cTime::operator -(const cTime &rhs)
{
	Sint32 difference = CalcSum() - rhs.CalcSum();
	cTime result(difference);
	
	return (result);
}

// assignment add (milliseconds)
cTime &cTime::operator += (Sint32 _ms)
{
	Add(_ms);
	return (*this);
}

// comparison operators
int cTime::operator == (const cTime &rhs)
{
	return (CalcSum() == rhs.CalcSum());
}
int cTime::operator != (const cTime &rhs) 
{
	return (CalcSum() != rhs.CalcSum());
}
int cTime::operator < (const cTime &rhs)
{
	return (CalcSum() < rhs.CalcSum());
}
int cTime::operator > (const cTime &rhs)
{
	return (CalcSum() > rhs.CalcSum());
}
int cTime::operator <= (const cTime &rhs)
{
	return (CalcSum() < rhs.CalcSum() ||
			CalcSum() == rhs.CalcSum());
}
int cTime::operator >= (const cTime &rhs)
{
	return (CalcSum() > rhs.CalcSum() ||
			CalcSum() == rhs.CalcSum());
}

void cTime::ToString()
{
	cout << "Time: ";
	cout.fill('0');
	cout.width(2);
	cout << mHours << "/";
	cout.fill('0');
	cout.width(2);
	cout << mMinutes << "/";
	cout.fill('0');
	cout.width(2);
	cout << mSeconds << "/";
	cout.fill('0');
	cout.width(3);
	cout << mMilliseconds << endl;
}

Sint32 cTime::CalcSum() const
{
	Sint32	mSumMS = mHours * 60 * 60 * 1000 +
			mMinutes * 60 * 1000 +
			mSeconds * 1000 +
			mMilliseconds;
	return mSumMS;
}

void cTime::Add(Sint32 _SumMilliseconds)
{
	mMilliseconds += _SumMilliseconds;

	while(mMilliseconds >= 1000)
	{
		mMilliseconds -= 1000;
		mSeconds++;
		if(mSeconds >= 60)
		{
			mSeconds -=60;
			mMinutes++;
		}
		if(mMinutes >= 60)
		{
			mMinutes -= 60;
			mHours++;
		}
	}
}
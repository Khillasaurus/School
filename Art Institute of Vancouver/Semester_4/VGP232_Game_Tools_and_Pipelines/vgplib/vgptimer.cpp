//-----------------------------
// File:		vgptimer.cpp
// Created:		2012/1/26
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "vgp/vgptimer.h"
#include <windows.h>

cTimer::cTimer()
:	mIsRunning(false)
,	mStartTime(0)
,	mStopTime(0)
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	mFrequency = freq.QuadPart;
}

void cTimer::Start()
{
	mIsRunning = true;
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);
	mStartTime = mStopTime = now.QuadPart;
}

void cTimer::Stop()
{
	mIsRunning = false;
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now );
	mStopTime = now.QuadPart;
}

cTime cTimer::GetElapsed()
{
	cTime elapsed;

	if( mIsRunning )
	{
		LARGE_INTEGER now;
		QueryPerformanceCounter( &now );
		mStopTime = now.QuadPart;
	}

	Uint64 lap = mStopTime - mStartTime;

	//Uint64 seconds = lap / mFrequency;
	Uint64 mseconds = lap / (mFrequency / 1000);

	Sint32 ms = (mseconds & 0x00000000ffffffff);

	elapsed.Add( ms );	

	return elapsed;
}





/*

// In Class Work Follows Here




#include "stdafx.h"
#include "vgp/vgptimer.h"
#include <windows.h>

cTimer::cTimer()
:	mIsRunning( false )
,	mInterval( kFPSInfinite )
{
	Reset();
	LARGE_INTEGER freq;
	QueryPerformanceFrequency( &freq );
	mFrequency = freq.QuadPart;
}
cTimer::cTimer( Uint32 interval )
:	mIsRunning( false )
,	mInterval( interval )
{
	Reset();
	LARGE_INTEGER freq;
	QueryPerformanceFrequency( &freq );
	mFrequency = freq.QuadPart;
}

void cTimer::Reset()
{
	mStart = mStop = 0;
}
void cTimer::Start()
{
	mIsRunning = true;
	LARGE_INTEGER now;
	QueryPerformanceCounter( &now );
	mStartTime = mStopTime = now.QuadPart;
}
void cTimer::cTimer::Stop()
{
	mIsRunning = false;
	LARGE_INTEGER now;
	QueryPerformanceCounter( &now );
	mStop = now.QuadPart;
}
void cTimer::SetInterval( Uint32 Interval )
{
	mInterval = interval;
}
bool cTimer::Advance()
{
	if( mIsRunning )
	{
		if( mInterval == kFPSInfinite	||
			Elapsed() >= mInterval )
		{
		mStop -= mInterval;
			return true;
		}
	}
	return false;
}
Uint32 cTimer::Elapsed()
{
	if( mIsRunning )
	{
		LARGE_INTEGER now;
		QueryPerformanceCounter( &now );
		mStop = now.QuadPart;
	}

	Uint64 lap = mStop - mStart;

	//Uint64 seconds = lap / mFrequency;
	Uint64 mseconds = lap / (mFrequency / 1000);

	return U64toU32( mseconds );
}

*/











/*

void cTime::SetTimeEpoch()
{
	// t is number of seconds since jan 1 00:00 1970 UTC
	// convert from UTC to local
	time_t t = time(NULL);

	struct _timeb tstruct;
	_ftime( & tstruct ); // C4996

	Uint64 utcOffset = tstruct.timezone;

	timeStamp -= utcOffset;

	tm *pTm = gmtime(&t);

	//pTm->tm_year + 1900;
	//pTm->tm_mon;
	//pTm->tm_mday;
	mHour = pTm->tm_hour;
	mMin = pTm->m_min;
	mSec = pTm->tm_sec;
}

*/
#include "stdafx.h"
#include "common/vgptimer.h"
#include <windows.h>

cTimer::cTimer()
:	mIsRunning(false)
,	mStartTime(0)
,	mStopTime(0)
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency( &freq );
	mFrequency = freq.QuadPart;
}

void cTimer::Start()
{
	mIsRunning = true;
	LARGE_INTEGER now;
	QueryPerformanceCounter( &now );
	mStartTime = mStopTime = now.QuadPart;
}

void cTimer::Stop()
{
	mIsRunning = false;
	LARGE_INTEGER now;
	QueryPerformanceCounter( &now );
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
//-----------------------------
// File:		vgptimer.h
// Created:		2012/1/26
// Copyright:	Daniel Schenker
//-----------------------------

#ifndef _VGPTIMER_H
#define _VGPTIMER_H

#include "vgp/vgptime.h"

	// init from perftimer
	// start timer
	// update from perftimer
	// stop timer
	// get elapsed

class cTimer
{
public:
	cTimer();
	void Start();
	void Stop();
	cTime GetElapsed();

	bool mIsRunning;
	Uint64 mFrequency;
	Uint64 mStartTime;
	Uint64 mStopTime;

};

#endif _VGPTIMER_H









/*

//In Class Starts Here

#ifndef _vgptimer_H
#define _vgptimer_H

	// y/m/d h:m:s.ms

clas cTimer
{
public:
	enum:
	{
		kFPSInfinite = 0,
		kFPS30 = 32,
		kFPS60 = 16
	};
public:
	cTimer();
	cTimer( Uint32 interval );

	// does NOT stop timer (if running), does reset/end times
	void Reset();
	
	//
	void Start();
	
	//
	void Stop();
	
	//
	void SetInterval( Uint32 Interval );

	//return true when running timer has elapsed current interval
	bool Advance();

	// returns current elapsed milliseconds between stop and start time.
	Uint32 Elapsed();

protected:
	bool mIsRunning;
	Uint64 mStart;
	Uint64 mStop;
	Uint64 mInterval;

	//number of cycles/second of CPU
	Uint64 mFrequency;
};

#endif // _vgptimer_H

*/
#ifndef _VGPTIMER_H
#define _VGPTIMER_H

#include "common/vgptime.h"

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
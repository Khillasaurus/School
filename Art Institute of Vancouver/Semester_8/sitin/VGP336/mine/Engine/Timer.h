#ifndef INCLUDED_ENGINE_TIMER_H
#define INCLUDED_ENGINE_TIMER_H

//====================================================================================================
// Filename:	Timer.h
// Created by:	Peter Chan
// Description:	Class for high resolution timer
//====================================================================================================

//====================================================================================================
// Class Declarations
//====================================================================================================

class Timer
{
public:
	Timer();

	void Initialize();
	void Update();

	f32 GetElapsedTime() const;
	f32 GetTotalTime() const;
	f32 GetFramesPerSecond() const;

private:
	// http://msdn2.microsoft.com/en-us/library/aa383713.aspx
	LARGE_INTEGER mTicksPerSecond;
	LARGE_INTEGER mLastTick;
	LARGE_INTEGER mCurrentTick;
	
	f32 mElapsedTime;
	f32 mTotalTime;
	
	f32 mNextUpdateTime;
	f32 mFrameSinceLastSecond;
	f32 mFramesPerSecond;
};

#endif // #ifndef INCLUDED_ENGINE_TIMER_H
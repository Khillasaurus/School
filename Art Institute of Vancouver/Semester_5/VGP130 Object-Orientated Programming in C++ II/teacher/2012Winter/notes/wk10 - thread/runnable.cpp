// ------------------------------------------
// Filename:	wk9.cpp
// Created:		2012/03/02
// Copyright 2012 me
// ------------------------------------------

#include "stdafx.h"
#include "runnable.h"
#include <Windows.h>
#include <process.h>

bool cRunnable::Start()
{
	// for instanceCount ...
	//cThread::mInstanceId == ++sNextInstanceId;
	
	SetState( cRunnable::kStarting );
	mThreadHandle = (void*)_beginthreadex( NULL, (65535), &threadFunc, this, 0, &mThreadId );
	if( mThreadHandle )
	{
		// add counter or timer to limit amount of time we wait for thread to be running
		// because
		// thread might have started, then immediately stopped
		// before this function could detect its passing
		while( !IsState( cRunnable::kRunning ) )
		{
			::Sleep(1);
		}
		return true;
	}
	return false;
}

bool cRunnable::Stop()
{
	// prevent this object from calling stop() on itself inside its own Run()
	if( mThreadId != GetCurrentThreadId() )
	{
		SetState( cRunnable::kStopping );
		
		Uint32 kWaitTimeout = 10000; // in ms
		WaitForSingleObject( (HANDLE)mThreadHandle, kWaitTimeout );

		SetState( cRunnable::kStopped );
	}
	return true;
}
bool cRunnable::IsState(Uint32 state)
{
	bool rc = false;
	//Lock()
	rc = (mState == state);
	//Unlock()

	return rc;
}
void cRunnable::SetState(Uint32 state)
{
	//Lock()
	mState = state;
	//UnLocked();
}

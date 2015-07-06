
#include "stdafx.h"
#include "core/aithread.h"
#include <Windows.h>
#include <process.h>

cAIThread::cAIThread()
:	mThreadHandle(NULL)
,	mThreadId(0)
,	mState(kStopped)
{
}



void cAIThread::Start()
{
	// 0 == running , CREATE_SUSPENDED == paused 
	Uint32 initFlags = 0;
	mState = kStarting;
	mThreadHandle = (void*)_beginthreadex( NULL, (65535), threadfunc, this, 0, &mThreadId);
	if( mThreadHandle )
	{
		// happy happy
		if( initFlags == CREATE_SUSPENDED )
		{
			// start thread now...
			::ResumeThread(mThreadHandle);
		}

		//part that is not here... set thread's preferred processor

		// maybe loop until thread mState == kRunning

		//all done
		//isInit = true
	}
}

void cAIThread::Stop()
{
	if( mThreadId != GetCurrentThreadId() )
	{
		mState = kStopping;
		WaitForSingleObject( mThreadHandle, 10000 );
		mState = kStopped;
	}
}

void cAIThread::TerminateThread()
{
	CloseHandle(mThreadHandle);
	_endthreadex( 0 );
}
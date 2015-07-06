
#include "stdafx.h"
#include "core/ailog.h"
#include <stdio.h>
#include <stdarg.h>
#include "core/aierror.h"


namespace AIDebug
{
	cAILogger *cAILogger::spAILogger = NULL;

	cAILogger *cAILogger::GetInstance()
	{
		if( !spAILogger )
		{
			spAILogger = new cAILogger();
		}
		return spAILogger;
	}

	cAILogger::cAILogger()
	:	mLogMutex(5000)
	,	mLogSemaphore(5000)
	{
		Start();
	}
	void cAILogger::Log(const char *pFormat, ... )
	{
		char buf[8192];
		va_list va;
		va_start(va, pFormat);
		int sz = vsprintf(buf, pFormat, va);
		va_end(va);
		//strcat(buf,"\n");

		mLogMutex.GetMutex();
		mLogQueue.push( buf );
		mLogMutex.ReleaseMutex();

		// tell/notify/signal log thread there is a new log entry to process
		mLogSemaphore.ReleaseSemaphore();


		// !!!
		//Non-multithreaded test debug
		//DoWork();
		// !!!
	}

	Uint32 cAILogger::Run()
	{
		dbPrintf("ailogger is running");
		mState = kRunning;

		while( mState == cAIThread::kRunning )
		{
			DoWork();
		}

		dbPrintf("ailogger is stopping");

		TerminateThread();
		return 0;
	}
	
	void cAILogger::DoWork()
	{
		if( mLogSemaphore.GetSemaphore() == cAISemaphore::kSignaled )
		{
			if( mLogMutex.GetMutex() == cAIMutex::kSignaled )
			{
				// read queue
				// print/write log msg to disk
				dbPrintf( mLogQueue.front().c_str() );
				mLogQueue.pop();

				mLogMutex.ReleaseMutex();
			}
		}
	}
}

#include "stdafx.h"
#include "core/aisemaphore.h"
#include <Windows.h>
#include <process.h>


cAISemaphore::cAISemaphore( Uint32 timeout )
:	mSemaphore(NULL)
,	mTimeout(timeout)
{
	// create 
	mSemaphore = CreateSemaphore(NULL, 0, 100, NULL);
	if( !mSemaphore )
	{
		AIAssert(false);
	}
}

cAISemaphore::~cAISemaphore()
{
	CloseHandle( mSemaphore );
}

Uint32 cAISemaphore::GetSemaphore()
{
	Uint32 rc = WaitForSingleObject( mSemaphore, mTimeout );
	switch(rc)
	{
	case WAIT_OBJECT_0:
		return cAISemaphore::kSignaled;

	case WAIT_TIMEOUT:
		return cAISemaphore::kTimeout;

	default:
		// WAIT_FAILED || WAIT_ABANDONED
		return cAISemaphore::kFailed;
	}
}

void cAISemaphore::ReleaseSemaphore()
{
	::ReleaseSemaphore( mSemaphore, 1, NULL);
}



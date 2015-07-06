
#include "stdafx.h"
#include "core/aimutex.h"
#include <Windows.h>
#include <process.h>


cAIMutex::cAIMutex( Uint32 timeout )
:	mMutex(NULL)
,	mTimeout(timeout)
{
	// create 
	mMutex = CreateMutex( NULL, FALSE, NULL );
	if( !mMutex )
	{
		AIAssert(false);
	}
}

cAIMutex::~cAIMutex()
{
	CloseHandle( mMutex );
}

Uint32 cAIMutex::GetMutex()
{
	Uint32 rc = WaitForSingleObject( mMutex, mTimeout );
	switch(rc)
	{
	case WAIT_OBJECT_0:
		return cAIMutex::kSignaled;

	case WAIT_TIMEOUT:
		return cAIMutex::kTimeout;

	default:
		// WAIT_FAILED || WAIT_ABANDONED
		return cAIMutex::kFailed;
	}
}

void cAIMutex::ReleaseMutex()
{
	::ReleaseMutex( mMutex );
}

//
// File: aisemaphore.h 
// Date: 2012/04/02
// Copyright 2012 Me
//

#ifndef __AISEMAPHORE_H
#define __AISEMAPHORE_H

class cAISemaphore
{
public:
	enum
	{
		kSignaled,
		kTimeout,
		kFailed
	};

public: // cAISemaphore
	cAISemaphore( Uint32 timeout );
	~cAISemaphore();

	Uint32 GetSemaphore();

	void ReleaseSemaphore();

protected: // member vars

	void *mSemaphore;
	Uint32 mTimeout;
};


#endif

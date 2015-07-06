//
// File: aimutex.h 
// Date: 2012/04/02
// Copyright 2012 Me
//

#ifndef __AIMUTEX_H
#define __AIMUTEX_H

class cAIMutex
{
public:
	enum
	{
		kSignaled,
		kTimeout,
		kFailed
	};

public: // cAIMutex
	cAIMutex( Uint32 timeout );
	~cAIMutex();

	Uint32 GetMutex();

	void ReleaseMutex();

protected: // member vars

	void *mMutex;
	Uint32 mTimeout;
};

#endif // __AIMUTEX_H

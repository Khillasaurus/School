// file:	tunknown.h
// created:	2012/01/20
// Copyright 2012 by Me

#ifndef __tUnknown_H
#define __tUnknown_H

#include "vgp/iobject.h"

template <class T>
class tUnknown : public T
{
public: // tUnknown
    tUnknown();

public: // cIObject
	virtual Uint32 AddRef()
	{
		return ++mRefCount;
	}
	virtual Uint32 Release()
	{
		if( --mRefCount <= 0 )
		{
			delete this;
			return 0;
		}
		return mRefCount;
	}

	volatile Sint32 mRefCount;
};

template<class T> 
tUnknown<T>::tUnknown()
: mRefCount(0)
{
}



#endif // __tUnknown_H

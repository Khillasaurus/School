// file:	iobject.h
// created:	2012/01/20
// Copyright 2012 by Me

#ifndef __cIObject_H
#define __cIObject_H

class cIObject
{
public: // cIObject
	virtual ~cIObject(){}
	virtual Uint32 AddRef() = 0;
	virtual Uint32 Release() = 0;
};



#endif // __cIObject_H

// file:	base.h
// created:	2012/01/27
// Copyright 2012 by Me

#ifndef __cBase_H
#define __cBase_H

class cBase
{
public: // cBase
	enum
	{
		kIID = 0x00000001
	};
	cBase() : mIsTrue(false){}

	virtual void Test() = 0;
	virtual bool QI(Uint32 iid, void **ppvObj) = 0;

	bool mIsTrue;
};



#endif // __cBase_H

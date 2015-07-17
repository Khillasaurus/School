// file:	sub1.h
// created:	2012/01/27
// Copyright 2012 by Me

#ifndef __cSub1_H
#define __cSub1_H

#include "base.h"

class cSub1 : public cBase
{
public: // 
	enum
	{
		kIID = 0x00000002
	};
	virtual bool Get(){ return mIsTrue; }
};



#endif // __cSub1_H

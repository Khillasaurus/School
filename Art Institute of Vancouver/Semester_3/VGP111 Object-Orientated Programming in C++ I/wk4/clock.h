//-----------------------------
// File:		clock.h
// Created:		2012/1/26
// Copyright:	Daniel Schenker
//-----------------------------

#ifndef __cClock_H
#define __cClock_H

#include "Windows.h"

class cClock
{
public:	
	SYSTEMTIME stStart;
	SYSTEMTIME stNow;
	void timer();
};

#endif // __cClock_H
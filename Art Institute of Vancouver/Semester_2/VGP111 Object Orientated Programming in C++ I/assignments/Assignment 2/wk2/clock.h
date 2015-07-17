// file: clock.h
// created: 2011/10/21
//

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
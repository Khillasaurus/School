// file: vgptime.h
// created: 2011/10/21
//

#ifndef __VGPTIME_H
#define __VGPTIME_H

//include <windows.h>

// forward declarations
struct _SYSTEMTIME;

class cTime
{
public:

//functions that are automatically defined when you create a class or structure are:
	// default constructor
	// destructor
	// copy constructor
	// assignment operator
	// pointer operator
	// reference operator

	cTime();
	//this has to exist because a referencer must not equal null or else there will be errors
	cTime(const cTime &rhs); //rhs.mHours
	//this may not exist if the pointer points to null so be careful
	cTime(const cTime *rhs); //rhs->mHours
	cTime(const _SYSTEMTIME &st);
	cTime(Sint32 h, Sint32 m, Sint32 s, Sint32 ms = 0);
	cTime(Sint32 _SumMilliseconds);

	cTime &operator =(const cTime &rhs);
	cTime operator -(const cTime &rhs);
	cTime &operator +=(Sint32 _ms);

	int operator ==(const cTime &rhs);
	int operator !=(const cTime &rhs);
	int operator <(const cTime &rhs);
	int operator >(const cTime &rhs);
	int operator <=(const cTime &rhs);
	int operator >=(const cTime &rhs);
	

	void ToString();

	Sint32 CalcSum() const;
	void Add(Sint32 _SumMilliseconds );

protected:
	Sint32 mHours;
	Sint32 mMinutes;
	Sint32 mSeconds;
	Sint32 mMilliseconds;
};

#endif	//__VGPTIME_H
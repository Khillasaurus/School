//-----------------------------
// File:		vgptime.h
// Created:		2012/1/20
// Copyright:	Daniel Schenker
//-----------------------------

#ifndef _VGPTIME_H
#define _VGPTIME_H

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

	// default constructor
	cTime();
	//this has to exist because a referencer must not equal null or else there will be errors
	// copy constructor
	cTime(const cTime &rhs); //rhs.mHours
	//this may not exist if the pointer points to null so be careful
	cTime(const cTime *rhs); //rhs->mHours
	cTime(const _SYSTEMTIME &st);
	cTime(Sint32 h, Sint32 m, Sint32 s, Sint32 ms = 0);
	cTime(Sint32 _SumMilliseconds);

	// assignment operator
	cTime &operator = (const cTime &rhs);
	// subtract
	cTime operator - (const cTime &rhs);
	// assignment add
	cTime &operator += (Sint32 _ms);

	// comparison operators
	int operator == (const cTime &rhs);
	int operator != (const cTime &rhs);
	int operator < (const cTime &rhs);
	int operator > (const cTime &rhs);
	int operator <= (const cTime &rhs);
	int operator >= (const cTime &rhs);

	// initializer helper function
	Sint32 CalcSum() const;
	void Add(Sint32 _SumMilliseconds);
	void ToString();
protected:
	Sint32 mHours;
	Sint32 mMinutes;
	Sint32 mSeconds;
	Sint32 mMilliseconds;
};

#endif _VGPTIME_H

/*
void LessonWeek3b()
{
	//~~time
	//DONE: set time by UTC or local
	//reset() (sets all components to zero)
	//set time by component... everything is zero except for what we set
	// y/m/d h:m:s:ms
	//set time from another time
	//	copy contructor
	//	assignment operator
	//compare times (earlier/equal/later)
	//	operator != == < <= > >=
	//print time (inserter to cout)
	//add time (aka defines end time)
	//subtract time (aka defines elapsed time)
}
*/
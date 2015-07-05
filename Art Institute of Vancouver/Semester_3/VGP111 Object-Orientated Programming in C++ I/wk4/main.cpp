//-----------------------------
// File:		main.cpp
// Created:		2012/1/26
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "Windows.h"
#include "vgp/vgptime.h"

//Function Prototypes
bool UnitTest();

// -------------------------
int _tmain(int argc, _TCHAR* argv[])
{


	// decl a default time
	cTime a;

	// a.mHours == 0

	// decl a time set to 1:15:30 (and :0 ms)
	cTime b( 1, 15, 30 );

	SYSTEMTIME st;
	//GetSystemTime(&st);
	GetLocalTime(&st);
		// regular constructor
	cTime now(st);
	
	// decl a time set to the value of b
	cTime c(b); // const

	// copy c to d
		// equality operator
	cTime d = c;	// half as efficient as cTime d( c );

	a.ToString();
	b.ToString();
	c.ToString();
	d.ToString();
	now.ToString();

	if(c == b)
	{
		cout << "c == b" << endl;
	}
	else
	{
		cout << "c != b" << endl;
	}

	cTime stopTime(0, 0, 30);
	cTime clock; //0, 0, 0
	cTime frameTime(0, 0, 1); //1 frame per second
	GetLocalTime(&st);
	cTime before(st);

	while(clock < stopTime)
	{
		GetLocalTime(&st);
		cTime now(st);
		cTime elapsed = now - before;
		if(elapsed >= frameTime)
		{
			clock += (elapsed.CalcSum());
			clock.ToString();
			before = now;
		}
	}

	//::OutputDebugString("Hello World\n"); //great to use later on for debugging

	cout << "Time is up!" << endl;

	return 0;
}







/*

//InClass Work Follows Here


#include "stdafx.h"
#include "Windows.h"
#include "vgp/vgptime.h"

// -------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	cTime theTime;
	cTimer frameTimer( kFPS30 );
	bool isRunning = true;

	frameTimer.SetInterval( cTimer::kFPS30 );

	//theTime.SetTimeLocal();
	//theTime.clear();

	frameTimer.Start();
	while( isRunning ) 
	{
		if( frameTimer.Advance() )
		{
			//theTime += framTimer.Elapsed();
			//print time;
		}
	}

}

*/
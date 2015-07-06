//-----------------------------
// File:		logtest.cpp
// Created:		2012/04/02
// Copyright:	Daniel Schenker
//-----------------------------

// logtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "core/aierror.h"


int _tmain(int argc, _TCHAR* argv[])
{
	bool isFalse = false;

	dbPrintf("hello world");
	
	while(1)
	{
		dbPrintf("pre assert");
		AIAssert(true);

		dbPrintf("post assert");
		AIAssertMsg(false, "error message - unit test");
		
		//int a = 10;
		//AIAssertFormated(a == 100, ("a doesn't equal to 100!!! a's value is %d", a) );
	}

	return 0;
}
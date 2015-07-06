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
		AIAssert( isFalse );
		dbPrintf("post assert");
		AIAssertMsg( isFalse, "UnitTest" );
		dbPrintf("post assert 2");
	}


	return 0;
}


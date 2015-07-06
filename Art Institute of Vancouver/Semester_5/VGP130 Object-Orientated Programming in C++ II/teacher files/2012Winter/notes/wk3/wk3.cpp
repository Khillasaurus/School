// wk1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


class cTest;

bool TestFactory( cTest **ppTest );



class cTest : public tUnknown<cIObject>
{
public:
	cTest()
	{
		std::cout << "cTest()" << std::endl;
	}
	virtual ~cTest()
	{
		std::cout << "~cTest()" << std::endl;
	}
	int mX;
};

int _tmain(int argc, _TCHAR* argv[])
{
	cTest *pTest;
	pTest = new cTest();
	pTest->mX = 5;
	delete pTest;

	pTest = new cTest();
	pTest->AddRef();
	pTest->mX = 5;
	pTest->Release();

	tAutoPtr<cTest> pAutoTest = new cTest;
	pAutoTest = NULL;

	{
		tAutoPtr<cTest> pAutoTest = new cTest;
	}

	{
		tAutoPtr<cTest> pAutoTest;
		if( TestFactory( pAutoTest.AsPPObj() ) )
		{
			std::cout << "huzzah" << std::endl;
		}
	}
	return 0;
}

bool TestFactory( cTest **ppTest )
{
	if(ppTest)
	{
	    *ppTest = new cTest;
		(*ppTest)->AddRef();
		return true;
	}
	return false;
}

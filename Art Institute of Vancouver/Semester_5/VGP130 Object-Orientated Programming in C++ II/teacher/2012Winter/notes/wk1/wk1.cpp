// wk1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory.h>
#include <new>

class cThing
{
public:
	cThing():x(1),isTrue(true){}	// default constructor
	//cThing(int _x):x(_x){}	// default constructor
	// cThing a(cThing());
	//cThing(const cThing &rhs){}			// copy constructor
	//~cThing(){}			// destructor
	// cThing a = cThing();
	//cThing &operator =(const cThing &rhs){return *this;}// assignment operator

	int x;
	bool isTrue;
};

class cWidget
{
public:
	int x;
	int y;
};

//union bla
//{
//	cWidget a;
//	cThing b;
//};

int _tmain(int argc, _TCHAR* argv[])
{
	cThing *pThing;
	pThing = new cThing[2];
	//memset(pThing,0,sizeof(cThing)*2);
	delete pThing;

	const int kAlignment = 8;
	int reqsize = 7;
	int alignedSize = (reqsize + (kAlignment-1)) & ~(kAlignment - 1);

	// write a placement new memory manager
	// the mem mgr is a class with "createobject(), releaseObject()" functions
	// mgr must manage all the 'blocks'
	// initizalize with however many blocks you feel allows you to do all unit tests
	// reusable 'blocks'
	// unit tests can be implemented as its own class of a sequence of specific tests
	// ex: alloc, alloc, alloc, free, alloc, free free, 
	//     alloc,alloc, free free, free 

	//int blockSize = sizeof(bla);
	//char * pMemory;
	//pMemory = new char[ blockSize * 1000];

	//pThing = new(pMemory) cThing;
	//pThing->~cThing();

	//delete [] pMemory;


	return 0;
}


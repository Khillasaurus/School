// ------------------------------------------
// Filename:	wk9.cpp
// Created:		2012/03/02
// Copyright 2012 me
// ------------------------------------------

#include "stdafx.h"
#include "app.h"
#include <Windows.h>

class MarksMutex
{
public:
	HANDLE mMutex;
	enum{ kSig, kTimeout, kErr };
	MarksMutex() {HANDLE mMutex = CreateMutex (NULL, FALSE, NULL);}
	int Lock(){	
		DWORD mLastStatus = WaitForSingleObject( mMutex, 0 );
		switch( mLastStatus )
		{
		case WAIT_OBJECT_0: return kSig;
		case WAIT_TIMEOUT:  return kTimeout;
		default:
			//( rc == WAIT_FAILED || rc >= WAIT_ABANDONED_0 )
			return kErr;
		}
	}
	void Unlock(){ReleaseMutex( mMutex );}
};

int MyCompare(const void *lhs, const void *rhs)
{
	if ( *(char*)lhs < *(char*)rhs )
	{
		return -1;
	}
	else if ( *(char*)lhs == *(char*)rhs )
	{
		return 0;
	}
	else //if ( *(char*)lhs > *(char*)rhs )
	{
		return 1;
	}
}

//
void food()
{
	printf("yummy\n");
}


int _tmain(int argc, _TCHAR* argv[])
{
	int *pInt;

	void (*pFood)();
	pFood = &food;
	food();
	pFood();

	char elements[11] = { "aldiengipw" };

	printf("%s\n", elements);

	qsort( &elements[0], 10, sizeof(char), &MyCompare );

	printf("%s\n", elements);


	//typedef R (T::*tOnEvent)( E *);
	//tOnEvent pFunc_OnEvent;

	void (App::*pOnEvent)(Uint32);

	pOnEvent = &App::OnEvent;


	App myApp;
	myApp.x = 5;
	App myApp1;
	myApp1.x = 10;


	(myApp.*pOnEvent)(2);
	(myApp1.*pOnEvent)(2);


	myApp.Run();



	return 0;
}

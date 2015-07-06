// ------------------------------------------
// Filename:	wk9.cpp
// Created:		2012/03/02
// Copyright 2012 me
// ------------------------------------------

#include "stdafx.h"
#include "app.h"
#include <Windows.h>

// ------------------------------------------

AppWorker::AppWorker()
:	mIsRunning(true)
{
}

// ------------------------------------------

AppWorker::~AppWorker()
{
}

// ------------------------------------------

Sint32 AppWorker::Run()
{
	// i am running in a thread.

	for(Uint32 i = 0; i < 10; ++i )
	{
		printf("hi from thread\n");
		::Sleep(100);
	}
	printf("thread is done\n");

	return 0;
}


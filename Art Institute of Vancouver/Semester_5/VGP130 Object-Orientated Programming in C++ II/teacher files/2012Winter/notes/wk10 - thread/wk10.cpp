// ------------------------------------------
// Filename:	wk9.cpp
// Created:		2012/03/02
// Copyright 2012 me
// ------------------------------------------

#include "stdafx.h"
#include <Windows.h>
#include "app.h"

volatile bool isRunning = false;

int _tmain(int argc, _TCHAR* argv[])
{
	AppWorker worker;

	worker.Start();

	while(worker.IsState( cRunnable::kRunning) )
	{
		printf("main is waiting for thread to finish\n");
		::Sleep(32);
	}

	return 0;
}

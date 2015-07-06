// ------------------------------------------
// Filename:	wk9.cpp
// Created:		2012/03/02
// Copyright 2012 me
// ------------------------------------------

#ifndef __APP_H
#define __APP_H

#include "runnable.h"

class AppWorker : public cRunnable
{
public:

public:
	AppWorker();
	virtual ~AppWorker();

public: // cRunnable
	virtual Sint32 Run();

public:
	bool mIsRunning;

	int x;
};

#endif //__APP_H
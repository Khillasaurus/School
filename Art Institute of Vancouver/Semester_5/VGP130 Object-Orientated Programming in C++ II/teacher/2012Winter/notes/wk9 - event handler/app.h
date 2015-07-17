// ------------------------------------------
// Filename:	wk9.cpp
// Created:		2012/03/02
// Copyright 2012 me
// ------------------------------------------

#ifndef __APP_H
#define __APP_H

#include "eventhandler.h"

class App : public cIEventTarget
{
public:
	enum eEventIds
	{
		kEventInit,
		kEventShutdown
	};

public:
	App();
	virtual ~App();
	bool Run();

public: // cIEventTarget
	virtual void OnEvent(Uint32 eventId);

public:
	bool mIsRunning;
	cEventHandler mEventHandler;

	int x;
};

#endif //__APP_H
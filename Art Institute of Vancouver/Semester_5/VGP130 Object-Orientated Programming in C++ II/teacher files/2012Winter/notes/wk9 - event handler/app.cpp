// ------------------------------------------
// Filename:	wk9.cpp
// Created:		2012/03/02
// Copyright 2012 me
// ------------------------------------------

#include "stdafx.h"
#include "app.h"

// ------------------------------------------

App::App()
:	mIsRunning(true)
{
}

// ------------------------------------------

App::~App()
{
}

// ------------------------------------------

bool App::Run()
{
	// v3
	//mEventHandler.RegisterTarget( 
	//	kEventInit, 
	//	this, 
	//	&App::OnInit() );

	//RegisterTarget( Uint32, App *,  void (App::*pFunc)(Uint32) );
	
	//v2
	mEventHandler.RegisterTarget( kEventInit, this );
	mEventHandler.RegisterTarget( kEventShutdown, static_cast<cIEventTarget*>(this) );
	//v1
	//mEventHandler.RegisterTarget( kEventShutdown );

	mEventHandler.PostEvent( kEventInit );

	while(mIsRunning)
	{
		// an event handler
		//	aka message pump
		//	aka message handler
		//	aka message queue
		//  aka message dispatcher
		//	aka event queue

		mEventHandler.HandleEvents();
	}
	return true;
}

// ------------------------------------------

void App::OnEvent(Uint32 eventId )
{
	printf("x = %d\n", x );


	switch(eventId)
	{
	case kEventInit:
		{
			mEventHandler.PostEvent( kEventShutdown );
		}
		break;

	case kEventShutdown:
		mIsRunning = false;
		break;
	}
}

//Uint32 App::OnInit(cInitEvent *pEvent)
//{
//	return 0;
//}
// ------------------------------------------
// Filename:	runnable.h
// Created:		2012/03/09
// Copyright 2012 me
// ------------------------------------------

#ifndef __RUNNABLE_H
#define __RUNNABLE_H


//class cFinder : public cRunnable
//{
//};
//
//cFinder myFinder;
//
//myFinder.Start();
//
//myFinder.PostFindRequest( cRequest("name") );
//
//// poll for an answer  YUCK!!
////myFinder.IsFindRequestDone();




class cRunnable
{
public:
	enum eRunStates
	{
		kStopped,
		kStarting,
		kRunning,
		kStopping
	};
public:
	friend Uint32 __stdcall threadFunc( void*pContext );

	cRunnable()
	:	mState(kStopped)
	{
	}
	virtual bool Start();
	virtual bool Stop();
	bool IsState(Uint32 state);
	void SetState(Uint32 state);

	// subclass to impl
	virtual Sint32 Run() = 0;


protected:
	volatile Uint32 mState;
	void * mThreadHandle;
	Uint32 mThreadId;

};


inline Uint32 __stdcall threadFunc( void*pContext )
{
	cRunnable *pRunnable = reinterpret_cast<cRunnable*>(pContext);
	pRunnable->SetState( cRunnable::kRunning );
	pRunnable->Run();
	pRunnable->SetState( cRunnable::kStopping );
	return 0;
}


#endif //__RUNNABLE_H
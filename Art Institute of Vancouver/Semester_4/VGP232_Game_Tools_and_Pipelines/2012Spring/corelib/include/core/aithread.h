//
// File: aithread.h 
// Date: 2012/04/02
// Copyright 2012 Me
//

#ifndef __AITHREAD_H
#define __AITHREAD_H

class cAIThread
{
public:
	enum
	{
		kStopped,
		kStarting,
		kRunning,
		kStopping
	};
public: // cAIThread
	cAIThread();
	void Start();
	void Stop();
	virtual Uint32 Run() = 0;

	void TerminateThread();

	friend unsigned __stdcall threadfunc(void *pvarg);

protected:
	void *mThreadHandle;
	Uint32 mThreadId;


	volatile Uint32 mState;
};

inline unsigned __stdcall threadfunc(void *pvarg)
{
	cAIThread *pThread = reinterpret_cast<cAIThread*>(pvarg);
	return pThread->Run();
}

#endif

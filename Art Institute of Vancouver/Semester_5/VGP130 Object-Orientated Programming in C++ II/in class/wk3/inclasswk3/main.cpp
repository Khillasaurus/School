// inclasswk3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <math.h>
#include "eventman.h"

class cKeyEvent : public cEvent
{
public:
	static const int kKeyEventId = 10;
	cKeyEvent()
	:	cEvent(kKeyEventId)
	{
		strcpy(msg, "hi");
	}

	char msg[16];
};

class cMyHandler : public cEventSubscriber
{
public:
	virtual void HandleEvent(const cEvent* pEvent);
};

void cMyHandler::HandleEvent(const cEvent* pEvent)
{
	cout << "cMyHandler::HandleEvent(" << pEvent->mId << ")" << endl;

	if(pEvent->mId == cKeyEvent::kKeyEventId)
	{
		const cKeyEvent* pKeyEvt = static_cast<const cKeyEvent*>(pEvent);
		cout << "keyEvent = " << pKeyEvt->msg << endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	cEventMan eventMan;
	cMyHandler myHandler;

	eventMan.AddSubscriber(&myHandler);

	cAutoRefCount<cEvent> pEvent = new cEvent(1);
	eventMan.PostEvent(pEvent);

	cEvent* pSentEvent = new cEvent(2);
	eventMan.SendEvent(pSentEvent);
	pEvent = NULL;//this means that pEvent gets deleted here instead of when it goes out of scope

	cAutoRefCount<cKeyEvent> pKeyEvent = new cKeyEvent();
	eventMan.PostEvent(pKeyEvent);
	pKeyEvent = NULL;//this means that pEvent gets deleted here instead of when it goes out of scope

	while(1)
	{
		eventMan.Update();
		//inputMan.Update();
	}

	return 0;
}

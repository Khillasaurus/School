#include "stdafx.h"
#include "eventman.h"

cEventMan::~cEventMan()
{
	//todo : release all memory
}

void cEventMan::AddSubscriber(cEventSubscriber* pSub)
{
	mSubscribers.push_back(pSub);
}

void cEventMan::PostEvent(cEvent* pEvent)
{
	mMsgQ.push(pEvent);
}

void cEventMan::SendEvent(cEvent* pEvent)
{
	tSubscriberListIter it, itEnd;

	for(it = mSubscribers.begin(), itEnd = mSubscribers.end(); it != itEnd; ++it)
	{
		//handle events
		(*it)->HandleEvent(pEvent);
	}
}

void cEventMan::Update()
{
	//get next event
	int numMsgs = mMsgQ.size();
	cAutoRefCount<cEvent> pEvent;
	while(numMsgs)
	{
		//cEvent* pEvent = mMsgQ.front();
		pEvent = mMsgQ.front();
		mMsgQ.pop();
		SendEvent(pEvent);

		//pEvent = NULL;//not needed, just for aesthetic reasons or debuging reasons

		numMsgs--;
	}
}
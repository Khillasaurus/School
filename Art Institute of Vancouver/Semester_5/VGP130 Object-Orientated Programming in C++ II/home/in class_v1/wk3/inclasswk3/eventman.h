#ifndef __EVENTMAN_H
#define __EVENTMAN_H

class cEvent
{
public:
	cEvent(int id):	mId(id), mRefCount(0){}
	Sint32 AddRef()
	{
		return (++mRefCount);
	}
	Sint32 Release()
	{
		if(--mRefCount <= 0)
		{
			delete this;
			return 0;
		}
		return mRefCount;
	}
	int mId;
	signed int mRefCount;
};

class cEventSubscriber
{
public:
	virtual void HandleEvent(const cEvent* pEvent) = 0;
};

class cEventMan
{
public:
	~cEventMan();

	void AddSubscriber(cEventSubscriber* pSub);

	//event is posted to occur on next update
	void PostEvent(cEvent* pEvent);

	//event is dispatched immeditately
	void SendEvent(cEvent* pEvent);

	void Update();

protected:
	queue<cAutoRefCount<cEvent>> mMsgQ;

	typedef vector <cEventSubscriber*> tSubscriberList;
	typedef tSubscriberList::iterator tSubscriberListIter;
	tSubscriberList mSubscribers;
};

#endif
//-----------------------------
// File:		connectionpool.h
// Created:		2012/04/02
// Copyright:	Daniel Schenker
//-----------------------------

#ifndef __CONNECTIONPOOL_H
#define __CONNECTIONPOOL_H


class cConnectionPool()
{
public:
	void SetMsgQ(queue<cPacket*>* pMsgQ){mpMsgQ = pMsgQ;}
	void AddConnection(cConnectionTCp*);
	void Update();

protected:
	typedef list<cConnectionTCP *> tConnectionList;
	typedef tConnectionList::iterator tConnectionListIter;

	list<cConnectionTCP*> mConnections;

	fd_set mReadSet;
	fd_set mErrorSet;
	fd_set mWriteSet;
	int mHighFds;

	tMsgQ* mpMsgQ;
};

#endif //__CONNECTIONPOOL_H
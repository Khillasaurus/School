//
// File: connectionpool.h 
// Date: 2012/05/07
// Copyright 2012 Me
//

#ifndef __CONNECTIONPOOL_H
#define __CONNECTIONPOOL_H

//fwd decl
class cConnectionTCP;
class cPacket;

// --------------------
class cConnectionPool
{
public:
	cConnectionPool();

	void SetMsgQ( queue<cPacket*> *pMsgQ ){  mpMsgQ = pMsgQ; }
	void AddConnection(cConnectionTCP *pConnection);
	void Update();

	void SendToAll( cPacket *pPkt );

protected:
	typedef list<cConnectionTCP *> tConnectionList;
	typedef tConnectionList::iterator tConnectionListIter;
	tConnectionList mConnections;

    fd_set mReadSet;
    fd_set mErrorSet;
    fd_set mWriteSet;
	Uint32 mHighFds;

	queue<cPacket*> *mpMsgQ;
};

#endif

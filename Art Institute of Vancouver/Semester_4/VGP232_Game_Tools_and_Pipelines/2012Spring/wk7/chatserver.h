//
// File: chatserver.h 
// Date: 2012/05/14
// Copyright 2012 Me
//

#ifndef __cChatServer_H
#define __cChatServer_H

#include "net/connectionpool.h"

class cChatServer
{
public:
	cChatServer(Uint16 port);

	void Run();

protected:
	cConnectionPool mPool;
	queue<cPacket*> mMsgQ;
};

#endif
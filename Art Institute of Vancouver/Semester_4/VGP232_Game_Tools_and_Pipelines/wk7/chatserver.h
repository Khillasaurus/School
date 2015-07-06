#ifndef __cChatServer_H
#define __cChatServer_H

#include "../netlib/include/net/connectionpool.h"

class cChatServer
{
public:
	cChatServer(Uint16 port);

	void Run();

protected:
	cConnectionPool mPool;
	queue<cPacket*> mMsgQ;
}

#endif //__cChatServer_H
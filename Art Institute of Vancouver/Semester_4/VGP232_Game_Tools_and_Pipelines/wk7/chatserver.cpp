#include "stdafx.h"
#include "chatserver.h"
#include "net/packet.h"
#include "net/connectiontcp.h"

cChatServer::cChatServer(Uint16 port)
{
	AINet::NetworkSetup();

	mPool.SetMsgQ(&mMsgQ);

	cConnectionTCp* pServer = new cConnectionTCP();
	pServer->mPort = port;
	pServer->Bind();
	thePool.AddConnection(pServer);
}

void cChatServer::Run()
{
	while(1)
	{
		//update the pool
		mPool.Update();

		//process pkts
		if(!mMsgQ.empty())
		{
			cPacket* pPkt = mMsgQ.front();
			mMsgQ.pop();

			//todo: do something with pkt
			cout << "pkt: " < pPkt->GetDataPtr() << endl;

			mPool.SendToAll(pPkt);

			delete pPkt;
		}

	}
}
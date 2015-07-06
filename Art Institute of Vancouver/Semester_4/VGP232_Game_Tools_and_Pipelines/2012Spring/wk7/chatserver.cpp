//
// File: chatserver.h 
// Date: 2012/05/14
// Copyright 2012 Me
//

#include "stdafx.h"
#include "chatserver.h"
#include "net/netutils.h"
#include "net/packet.h"
#include "net/connectiontcp.h"


cChatServer::cChatServer(Uint16 port)
{
	AINet::NetworkSetup();

	mPool.SetMsgQ( &mMsgQ );

	cConnectionTCP *pServer = new cConnectionTCP();
	pServer->mPort = port;
	pServer->Bind();
	mPool.AddConnection(pServer);
}

void cChatServer::Run()
{
	while(1)
	{
		//update pool
		cout << "update" << endl;
		mPool.Update();

		//process pkts
		if( !mMsgQ.empty() )
		{
			cout << "got pkt" << endl;
			cPacket *pPkt = mMsgQ.front();
			mMsgQ.pop();

			//todo: do something with pkt
			cout << "pkt: " << pPkt->GetDataPtr() << endl;
			if( pPkt->GetDataSize() )
			{
				mPool.SendToAll( pPkt );
			}


			//delete pPkt;
		}
	}
}

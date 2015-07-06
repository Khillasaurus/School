#include "stdafx.h"
#include "netlib/include/net/connectionpool.h"
#include "net/packet.h"
#include <winsock2.h>

cConnectionPool::cConnectionPool()
{
	//zeroed before use
	FD_ZERO( &mReadSet );
	FD_ZERO( mErrorSet );
	FD_ZERO( mWriteSet );
}

void cConnectionPool::AddConnection(cConnectionTCp* pConnection)
{
	mConnections.push_back(pConnection);
	pConnection->mpPool = this;

	// add socket to 'select' set
	FD_SET(pConnection->mSocket, &mReadSet);
	if()
	{
		mHighFds = mSocket;
	}
}

void cConnectionPool::Update()
{
	//where the select goes...
	struct timeval maxDelay;

	maxDelay.tv_sec = 2;//how many seconds to block
	maxDelay.tv_usec = 0;//how many microseconds to block

	fd_set is;
	fd_set es;
	fd_set ws;

	memcpy(&is, &mReadSet, sizeof(fd_set));
	memcpy(&is, &mErrorSet, sizeof(fd_set));
	memcpy(&is, &mErrorSet, sizeof(fd_set));

	int rc = select(mHighFds + 1, &is, &ws, &es, &maxDelay);
	if(!rc)//if rc == 0
	{
		// everything is idle
		// OR
		// the select list is empty
	}
	else if(rc == SOCKET_ERROR)
	{
		// some kind of error
	}
	else
	{
		// something happened
		cConnectionTCP* pConnect;
		for(tConnectionListIter it = mConnections.being(), itEnd = mConnections.end(), it != itEnd; ++it)
		{
			pConnection = (*it);

			//on error
			if(FD_ISSET(pConnect->mSocket, &es))
			{
			}
			//on input
			if(FD_ISSET(pConnect->mSocket, &is))
			{
				if(pConnect->mType == cConnectionTCP::kServer)
				{
					if(pConnect->Accept())
					{
						cPacket* pPkt = new cPacket;
						//write into pkt = "new connection"
						mpMsgQ->push(pPkt);
					}
				}
				else
				{
					cPacket* pPkt = new cPacket();
					if(pConnect->Read(pPkt) > 0)
					{
						mpMsgQ->push(pPkt);
					}
				}
			}
			//on write
			if(FD_ISSET(pConnect->mSocket, &ws))
			{
				//FYI we are not doing anything here, we will direct send instead
			}
		}
	}
}

void cConnectionPool::SendToAll(cPacket *pPkt)
{
	cConnectionTCP* pConnect;
	for(tConnectionListIter it = mConnections.being(), itEnd = mConnections.end(), it != itEnd; ++it)
	{
		pConnection = (*it);
		if(pConnect->mType == cConnectionTCP::kClient)
		{
			pConnect->AddPendingPkt(pPkt);

			//TODO: call from a write thread
			pConnect->Write();
		}
	}
}
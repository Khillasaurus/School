//
// File: connectiontcp.h 
// Date: 2012/05/07
// Copyright 2012 Me
//

#include "stdafx.h"
#include "net/connectionpool.h"
#include "net/connectiontcp.h"
#include "net/packet.h"

cConnectionPool::cConnectionPool()
:	mHighFds(0)
{
	// zeroed before use
	FD_ZERO( &mReadSet );
	FD_ZERO( &mErrorSet );
	FD_ZERO( &mWriteSet );
}

// -------------------------------------------------------

void cConnectionPool::AddConnection(cConnectionTCP *pConnection)
{
	mConnections.push_back( pConnection );
	pConnection->mpPool = this;

	// add socket to 'select' set
    FD_SET(pConnection->mSocket, &mReadSet);
	if( pConnection->mSocket > mHighFds )
	{
		mHighFds = pConnection->mSocket;
	}
}

void cConnectionPool::Update()
{
	struct timeval maxDelay;

	maxDelay.tv_sec = 2;
	maxDelay.tv_usec = 0;

    fd_set is;
    fd_set es;
    fd_set ws;

	memcpy( &is, &mReadSet, sizeof( fd_set));
	memcpy( &ws, &mWriteSet, sizeof( fd_set));
	memcpy( &es, &mErrorSet, sizeof( fd_set));

 	int rc = select( mHighFds+1, &is, &ws, &es, &maxDelay);
	if( !rc )
	{
		// everything is idle 
		// OR
		// the select list is empty
	}
	else if (rc == SOCKET_ERROR)
	{
		// some kind of error
	}
	else
	{
		// something happened...
		cConnectionTCP *pConnect;
		tConnectionListIter it, itEnd;
		for( it = mConnections.begin(), itEnd = mConnections.end(); it != itEnd; ++it )
		{
			pConnect = (*it);

			// on error
			if( FD_ISSET( pConnect->mSocket, &es) )
			{
			}
			// on input
			else if( FD_ISSET( pConnect->mSocket, &is) )
			{
				if( pConnect->mType == cConnectionTCP::kServer )
				{
					if( pConnect->Accept() )
					{
						cPacket *pPkt = new cPacket();
						// write into pkt "new connection"
						mpMsgQ->push( pPkt );
					}
				}
				else
				{
					cPacket *pPkt = new cPacket();
					if( pConnect->Read(pPkt) > 0 )
					{
						mpMsgQ->push( pPkt );
					}
				}
			}
			// on write
			else if( FD_ISSET( pConnect->mSocket, &ws) )
			{
				//FYI: we are not doing anything here.. we will direct send instead
			}
		}
	}

}


void cConnectionPool::SendToAll( cPacket *pPkt )
{
	cConnectionTCP *pConnect;
	tConnectionListIter it, itEnd;
	for( it = mConnections.begin(), itEnd = mConnections.end(); it != itEnd; ++it )
	{
		pConnect = (*it);
		if( pConnect->mType == cConnectionTCP::kClient )
		{
			cPacket *pPacket = new cPacket();

			memcpy(pPacket->mpData, pPkt->mpData, pPkt->GetDataSize() );
			pPacket->SetDataSize( pPkt->GetDataSize() );

			pConnect->AddPendingPkt(pPacket);

			//TODO: called from a write thread
			pConnect->Write();
		}
	}
}


//
// File: connectiontcp.h 
// Date: 2012/05/07
// Copyright 2012 Me
//

#include "stdafx.h"
#include "net/connectiontcp.h"
#include "net/packet.h"
#include "net/connectionpool.h"
#include <Winsock2.h>

cConnectionTCP::cConnectionTCP()
:	mType(cConnectionTCP::kClient)
,	mSocket(INVALID_SOCKET)
,	mpPool(NULL)
,	mIpAddr(0)
,   mPort(9000)
,	mHasOutput(false)
,	mpCurrentWritePkt(NULL)
{
}
cConnectionTCP::~cConnectionTCP()
{
}
bool cConnectionTCP::Bind()
{
	mType = (cConnectionTCP::kServer);

	// create server socket
	mSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if( mSocket != INVALID_SOCKET )
	{
		// bind socket to a port
		// server address information
		struct sockaddr_in sa_server;		
		memset( &sa_server, 0, sizeof( sa_server ) );
		sa_server.sin_family = AF_INET;
		sa_server.sin_addr.s_addr = INADDR_ANY;			// inet_addr("172.31.227.103");
		sa_server.sin_port = htons( mPort );

		// bind the TCP socket to the server address
		int optval=1;
		if( setsockopt( mSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(int) ) == 0 )
		{
			if( bind( mSocket, (struct sockaddr *)&sa_server, sizeof(sa_server)) == 0 )
			{
				// Listen for connections.  Specify the backlog as 5
				const int kMaxBacklog = 5;
				if( listen( mSocket, kMaxBacklog ) == 0 )
				{
					// yay.. server sock is ready
					return true;
				}
				// else print error
			}
			// else print error
		}
		// else print error
	}
	// else print error
	return false;
}

// ---------------------------------------------------------------------------

bool cConnectionTCP::Accept()
{
	// accept the connection
	cConnectionTCP *pClientConnection = new cConnectionTCP();

	struct sockaddr_in addr;
	int addr_len;
	addr_len = sizeof( addr );
	pClientConnection->mSocket = accept( mSocket, (struct sockaddr *) &addr, &addr_len );
	if( pClientConnection->mSocket != INVALID_SOCKET )
	{
		pClientConnection->mIpAddr = addr.sin_addr.s_addr;
		pClientConnection->mPort = addr.sin_port;
		mpPool->AddConnection( pClientConnection );

		return true;
	}
	// else print error
	delete pClientConnection;

	return false;
}

// ---------------------------------------------------------------------------

Sint32 cConnectionTCP::Read(cPacket *pPkt)
{
	int bytesRead = recv( mSocket, pPkt->GetDataPtr(), pPkt->GetTrueSize(), 0 );

	if( bytesRead > 0 )
	{
		// that is how many bytes we read
		pPkt->SetDataSize( pPkt->GetDataSize() + bytesRead );
		return (pPkt->GetDataSize());
	}
	else if( !bytesRead )
	{
		// the socket is dead
	}
	else if( bytesRead == SOCKET_ERROR )
	{
		// ack!
	}
	return 0;
}

// ---------------------------------------------------------------------------

Sint32 cConnectionTCP::Write()
{
	if( mHasOutput )
	{
		if( !mpCurrentWritePkt )
		{
			mpCurrentWritePkt = mWriteQueue.front();
			mWriteQueue.pop();
			if( mWriteQueue.empty() )
			{
				 mHasOutput = false;
			}
		}

		int byteswritten = send( mSocket, mpCurrentWritePkt->GetDataPtr(), mpCurrentWritePkt->GetDataSize(), 0 );

		if( byteswritten == SOCKET_ERROR )
		{
		}
		else if( !byteswritten  )
		{
			// just means that no bytes were written... says nothing about the health of the connection
		}
		else
		{
			// yay.. bytes were written
			mpCurrentWritePkt->UpdateWritten( byteswritten );

			if( !mpCurrentWritePkt->GetDataSize() )
			{
				delete mpCurrentWritePkt;
				mpCurrentWritePkt = NULL;
			}
		}
	}
	return 0;
}

// ---------------------------------------------------------------------------

void cConnectionTCP::AddPendingPkt(cPacket *pPkt)
{
	mWriteQueue.push( pPkt );
	mHasOutput = true;
}

// ---------------------------------------------------------------------------

void cConnectionTCP::Close()
{
	// hang "closed" sign 
	shutdown(mSocket,SD_BOTH);

	// die die die
	closesocket(mSocket);
}
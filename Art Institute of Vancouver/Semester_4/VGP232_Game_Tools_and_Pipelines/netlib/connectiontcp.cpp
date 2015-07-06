//-----------------------------
// File:		connectiontcp.cpp
// Created:		2012/04/02
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "net/connectiontcp.h"
#include "net/packet.h"
#include <winsock2.h>

cConnectionTCP::cConnectionTCP()
:	mType(cConnectionTCP::kClient)
,	mSocket(INVALID_SOCKET)
,	mpPool(NULL)
,	IpAddr(0)
{
}

cConnectionTCP::~cConnectionTCP()
{
}

// server methods
bool cConnectionTCP::Bind()
{
	// create server socket
	mSocket = kServer;//mSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);//Uint32 mSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(mSocket != INVALID_SOCKET)
	{
		// bind socket to a port
		// server address information
		struct sockaddr_in sa_server;
		memset(&sa_server, 0, sizeof(sa_server));
		sa_server.sin_family = AF_INET;
		sa_server.sin_addr.s_addr = INADDR_ANY/*inet_addr("172.31.227.140")*/;//replace with the value in cmd>ipconfig>ipv4
		sa_server.sin_port = mSocket;

		// bind the TCP socket to the server address
		int optval = 1;
		if(setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(int)) == 0)
		{
			if(bind(mSocket, (struct sockaddr *)&sa_server, sizeof(sa_server)) == 0)//if it succeeded it should equal 0
			{
				// listen
				const int kMaxBackLog = 5;
				if(listen(mSocket, kMaxBackLog) == 0)
				{
					// yay.. server socket is ready
				}
				//else print error
			}
			//else print error
		}
		//else print error
	}
	//else print error
	
	return false;
}

bool cConnectionTCP::Accept()
{
	// accept the connection
	cConnectionTCP *pClientConnection = new cConnectionTCP();

	struct sockaddr_in addr;
	int addr_len;
	addr_len = sizeof(addr);
	pClientConnection->mSocket = acccept(mSocket, (struct sockaddr *) &addr, &addr_len);
	if(pClientConnection->mSocket != INVALID_SOCKET)
	{
		pClientConnection->mIpAddr = addr, sin_addr, s_addr;
		pClientConnection->mPort = addr.sin_port;
		mpPool->AddConnection(pClientConnection);

		return true;
	}
	// else print error
	delete pClientConnection;

	return false;
}

// general
Sint32 Read(cPacket *pPkt)
{
	int bytesRead = recv(socket, pPkt->GetDataPtr(), pPkt->GetTrueSize(), 0)

	if(bytesRead > 0)
	{
		//that is how many bytes we read
		dbPrintf("recvBuf = %s", recvBuffer);
		pPkt->SetDataSize(pPkt->GetDataSize() + bytesRead);
		return (pPkt->GetDataSize());
	}
	else if( !bytesRead)
	{
		// the socket is dead
	}
	else if(bytesRead == SOCKET_ERROR)
	{
		// ack!
	}

	return 0;
}


Sint32 Write()
{
	if(mHasOutput)
	{
		if(!mpCurrentWritePacket)
		{
			mpCurrentWritePacket = mWriteQueue.front();
			mWriteQueue.pop();
		}

		//int byteswritten = send(socket, &sendBuffer[0], strlen(sendBuffer), 0);
		int byteswritten = send(socket, mpCurrentWritePkt->GetDataPtr(), mpCurrentWritePacket->GetDataSize(), 0);

		if(byteswritten == SOCKET_ERROR)
		{
		}
		else if(!byteswritten)
		{
			// just means that no bytes were written... says nothing about the health of the connection
		}
		else
		{
			// yay.. bytes were written
			mpCurrentWritePkt->UpdateWritten(byteswritten);

			if(!mpCurrentWritePkt->GetDataSize())
			{
				delete mpCurrentWrite;
				mpCurrentWritePkt = NULL;
			}
		}
	}

	return 0;
}
// outboud
void AddPendingPkt(cPacket* pPkt)
{
	mWriteQueue.push(pPkt);
}

void cConnectionTCP::Close(Uint32 mSocket)
{
	//don't do both, they are seperate, both are here for reference sake
	// hang "closed" sign
	shutdown(mSocket, SD_BOTH);

	// die die die
	closesocket(mSocket);
}
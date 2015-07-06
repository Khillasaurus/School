// logtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "core/aierror.h"
#include "core/ailog.h"
#include <winsock2.h>
#include <Windows.h>
#include <process.h>
#include "net/connectiontcp.h"
#include "chatserver.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// server design

	// main thread
	//  listens for connections

	//  adds new connection to main thread (pool)

	//	has a waiting thread
	//		add new connection to thread (pool)


	// launches a new thread for each connection to do its work
	//	eg: read, do work, write, disconnect


	// server thread (ie waiting for connections)
	// read thread( blocked waiting for client connections that are ready to read )
	// write thread( blocked on a semaphore indicating ANY connection (in the pool) has outbound data )
	// main thread to route messages, do logic/work, handle login logic.


	// part list
	// ---------

	// cConnectionTCP   - a socket (client or server)
	// cConnectionPool	- fd_set/select handler
	// cPacket
	// cSafeQueue		- thread safe queue
	// cChatServer		- home for all the chat server logic
	// cLogin			- logical connected user

	cChatServer *pChatServer = new cChatServer( 7000 );
	if( pChatServer )
	{
		cout << "run" << endl;
		pChatServer->Run();
		delete pChatServer;
	}

	return 0;
}

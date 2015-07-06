//
// File: netutils.h 
// Date: 2012/05/14
// Copyright 2012 Me
//

#include "stdafx.h"
#include "net/netutils.h"
#include <winsock2.h>

namespace AINet
{
	void NetworkSetup()
	{
		WSADATA wsaData;
		int err;
		err = WSAStartup( MAKEWORD(2,0), &wsaData );
		if ( err == 0 )
		{
			//AILog( "cLGNetMan::InitTCPIP() %s,%s", wsaData.szDescription, wsaData.szSystemStatus );
			//sIsInitialized_TCPIP = true;
			cout << "wsa good" << endl;
		}
		else
		{
			// Tell the user that we could not find a usable WinSock DLL.
			cout << "wsa bad" << endl;
		}
	}
}
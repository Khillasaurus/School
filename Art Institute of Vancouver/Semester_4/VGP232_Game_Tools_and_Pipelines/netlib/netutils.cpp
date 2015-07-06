#include "stdafx.h"
#include "winsock2.h"
#include "netlib/include/netutils"

namespace AInet
{
	void NetworkSetup()
	{
		WSADATA wsaData;
		int err;
		err = WSAStartup( MAKEWORD(2, 0), &wsaData );
		if( err == 0 )
		{
			//AILog( "clGNetMan::InitTCPIP() %s, %s", wsaData.s2Description, wsaData.s2SystemStatus );
			//sIsInitialized TCPIP = true;
		}
		else
		{
			/* Tell the user that we could not find a usable */
			/* WinSock DLL */
		}
	}
}
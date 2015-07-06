////first half
//{
//	//-----------------------------
//	// File:		main.cpp
//	// Created:		2012/04/16
//	// Copyright:	Daniel Schenker
//	//-----------------------------
//
//	#include "stdafx.h"
//
//	class Object
//	{
//	public:
//		Object()
//		:mVal(0)
//		{
//		}
//		//pre
//		Object& operator ++()
//		{
//			(static_cast<Sint32>(InterlockedIncrement(reinterpret_cast<long volatile*>(&mVal))));
//			return (*this);
//		}
//		//pre
//		Object& operator --()
//		{
//			(static_cast<Sint32>(InterlockedDecrement(reinterpret_cast<long volatile*>(&mVal))));
//			return(*this);
//		}
//
//		volatile Sint32 mVal;
//	};
//
//	unsigned int __stdcall myWorkerThread(void *arg)
//	{
//		Object* pObj = (Object*)(arg);
//
//		while(1)
//		{
//			++(pObj);
//			--(pObj);
//			//pObj->mVal ++;
//			//pObj->mVal --;
//		}
//	}
//
//	int _tmain(int argc, _TCHAR* argv[])
//	{
//		dbPrintf("all done");
//
//		Object myObj;
//
//		_beginthreadex(NULL, (65535), myWorkerThread, &myObj, 0, NULL);
//
//		while(1)
//		{
//			//myObj.mVal++;
//
//			if ((++myObj).mVal <= 0)
//			{
//				dbPrintf("1: val is <= 0 %d", myObj.mVal);
//			}
//
//			//myObj.mVal --;
//
//			if ((--myObj).mVal <= 0)
//			{
//				dbPrintf("2: val is <= 0 %d", myObj.mVal);
//				//system("PAUSE");
//			}
//
//		}
//
//		//demo only
//		Sleep(100);
//
//		return 0;
//	}
//
//	// a1 - due w4
//	// level generator
//	//
//	// generate a 2D map
//	// - obstacle layer (trees/buildings/shrubbery/rocks/cars/rocks/etc)
//	// - treasure layer	(eggs, gold, silver, carrots, etc)
//	// - spawn location layer (spawn type etc)
//
//	// - aggregate all layers into ...
//	// - output single map file
//	//
//	// each layer is to be generated in a worker thread
//		//(either a you pass an object to a thread, which is a layer generator, or you pass a class in)
//	// impl to your own discretion, a timer object.
//	// 65k x 65k
//
//	// - hack visualizer
//	// - supply tool with x,y location, and output NxN grid as text output
//
//
//
//	//how to create a windows bitmap
//	//bing search: how to create a windows bitmap file c++
//	//http://www.vbforums.com/showthread.php?t=261522
//	//BITMAPINFOHEADER
//}




//second half

//-----------------------------
// File:		main.cpp
// Created:		2012/04/16
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
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
		// Tell the user
		// WinSock DLL
	}

	//TCPIP
	// RAW
	// ICMP - eg ping
	// UDP - connectionless
	// TCP - connected guaranteed ordering/delivery layer
	// sockets
	// open a socket

	// server addres information
	// the port must be in network byte order

	struct sockaddr_in sa_server;
	sa_server.sin_family		= AF_INET;
	sa_server.sin_port			= htons( 80 );
	sa_server.sin_addr.s_addr	= inet_addr("173.104.73.94"); // google.ca's ip addr
		//ip addresses can be found by entering the following in cmd:
			//ping websitename
	//for example school's website
	//sa_server.sin_addr.s_addr	= inet_addr("10.196.14.26"); // ai the hive's ip addr


	Uint32 mSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if( mSocket != INVALID_SOCKET )
	{
		if(connect( mSocket, (struct sockaddr *)&sa_server, sizeof(sa_server) ) != SOCKET_ERROR)
		{
			// yay.. we are connected!

			// send() "GET /  HTTP/1.1\r\n" == 0x0a0d
					//"GET /  HTTP/1.1\r\nUser-Agent: Mozilla/1.0\r\n\r\n" == 0x0a0d
						//the second carriage return lets the server know we are done sending our message and are now waiting for a reply
			char sendBuffer[128];
			sprintf( sendBuffer, "GET / HTTP/1.1\r\nserver: www.google.ca\r\n\r\n" );
			//school example continue'd
			//sprintf( sendBuffer, "GET / HTTP/1.1\r\nHost: thehive.artschool.com\r\nACCEPT: */*\r\nUSER_AGENT:aiclient/1    ......... I didn't write it all down in time

			int byteswritten = send( mSocket, &sendBuffer[0], strlen(sendBuffer), 0);

			if( byteswritten == SOCKET_ERROR )
			{
			}
			else if( !byteswritten )
			{
				// just means that no bytes were written... says nothing about the health of the connection
			}
			else
			{
				// yay.. bytes were written
			}

			// recv()
			char recvBuffer[1024];
			int bytesRead = recv( mSocket, &recvBuffer[0], 1024, 0 );

			if( bytesRead > 0 )
			{
				// that is how many bytes we read
				dbPrintf("recvBuf = %s", recvBuffer);
			}
			else if( !bytesRead )
			{
				// the socket is dead
			}
			else if( bytesRead == SOCKET_ERROR )
			{
				// ack!
			}

			closesocket(mSocket);
		}
	}

	// all done
	WSACleanup();

	return 0;
}
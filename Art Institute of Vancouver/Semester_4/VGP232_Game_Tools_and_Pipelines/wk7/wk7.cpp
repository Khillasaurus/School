//-----------------------------
// File:		main.cpp
// Created:		2012/05/07
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "chatserver.h"

int _tmain(int argc, _TCHAR* argv[])
{	
	//METHOD 1:
	// server design

	// main thread
	//	listens for connections

	//	adds new connection to main thread (pool)

	//	has a waiting thread
	//		add a new connection to thread

	//METHOD 2:
	// launches a new thread for each connection to do its work
	// eg: read, do work, write, disconnect

	//METHOD 3:
	// server thread (ie waiting for connections)
	// read thread (blocked waiting for client connections that are ready to read)
	// write thread (blocked on a semaphore indicating ANY connection (in the pool) has outbound data)
	// main thread to route messsages, do logic/work, handle the login logic


	// part list
	// ---------
	// cConnection			- a socket (client or server)
	// cConnectionPool		- fd_set/select handler
	// cPacket				- this is the buffer
	// cSafeQueue			- thread safe queue (necessary if there are at least 2 threads)
	// cChatServer			- home for all the chat server logic
	// cLogin				- logical conncected user

	cChatServer* pChatServer = new cChatServer(7000);
	if(pChatServer)
	{
		pChatServer->Run();
		delete pChatServer;
	}

	cConnectionPool thePool;

	//application run
	while(1)
	{
		thePool.Update();
	}


	return 0;
}









//class cMap
//{
//	//friend unsigned int __stdcall threadfoo(void *pvarg);//this allows the thread function to access anything inside this class
//
//	void Run()
//	{
//		x = 1;
//
//		//return 0; //0 is succesful, 1 is fail
//	}
//
//	int x;
//};
//
//unsigned int __stdcall threadfoo(void *pvarg)
//{
//	cMap *pMap = reinterpret_cast<cMap*>(pvarg);
//	sleep(1000);
//	printf("hi mom\n");
//
//	return 0;
//}
//
//int _tmain(int argc, _TCHAR* argv[])
//{	
//	// thread handle must be closed
//	//thread args
//	//concurrency via atomics, volatile, incrementing
//
//	cMap theMap;
//
//	void hThread = (void*)_beginthreadex(NULL, 65535, threadfoo, NULL, 0, NULL);
//
//	//this wait does nothing while waiting
//	WaitForSingleObject(hThread, 10000);//replace 10000 (the wait time) with INFINITE if you want to wait forever, but don't use this at shutdown just in case there are threads that aren't shutting down for some reason
//
//	CloseHandle(hThread);
//	
//	return 0;
//}
//
////A volatile command means load from memory (don't cache variable or use a variable from cache)
////In visual studio in windows, volatile adds fences for us. So be careful when using elsewhere
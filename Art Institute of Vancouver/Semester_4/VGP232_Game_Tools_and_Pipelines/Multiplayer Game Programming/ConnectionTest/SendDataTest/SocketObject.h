//--------------------------------
// File:		SocketObject.h
// Created:		2012/04/29
// Copyright:	Daniel Schenker
//--------------------------------
//Code partially based upon Todd Barron's textbook: Multiplayer Game Programming (2001)

#ifndef SOCKET_OBJECT
#define SOCKET_OBJECT

#include "stdafx.h"

struct stPacketHeader
{
	int		iType;
	int		iLength;
	int		iID;
	int		iCheckSum;
	int		iSender;
};

struct SocketTransmissionStruct 
{
	SOCKET		skSocket;
	char		szBuffer[64000];
	int			iWritePos;
	int			iReadPos;
	int			iTerminate;
};

// Class Object
class SocketObject  
{
	public:
		SOCKET						skSocket;
		int							iStatus;
		SocketTransmissionStruct	stReceive;	
		SocketTransmissionStruct	stSend;	
		DWORD						dwReceiveHandle;
		DWORD						dwSendHandle;

		// Constructor
		SocketObject();
		// Desctrucot
		~SocketObject();

		// Accept a client's request to connect
		bool Accept(SocketObject& skAcceptSocket);
		// Listen for clients to connect
		int Listen( void );
		// Open a server listening port
		int Bind(int iPort);
		// Close connection
		void Disconnect();
		// Connect to a server
		bool Connect(char* szServerAddress, int iPort);

		int Recv(char *szBuffer, int iBufLen, int iFlags);
		int Send(char *szBuffer, int iBufLen, int iFlags);

		// Misc Functions
		int iCalculateChecksum(stPacketHeader stHead);

		// Asynchronous Functions
		static void thrReceiveThread(SocketTransmissionStruct *rs);
		static void thrSendThread(SocketTransmissionStruct &rs);
		int vGetPacket(char *szbuffer);
};

#endif
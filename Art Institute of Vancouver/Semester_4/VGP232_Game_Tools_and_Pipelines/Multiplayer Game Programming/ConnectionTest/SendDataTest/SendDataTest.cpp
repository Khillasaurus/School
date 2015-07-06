//--------------------------------
// File:		SendDataTest.cpp
// Created:		2012/04/29
// Copyright:	Daniel Schenker
//--------------------------------
//Code partially based upon Todd Barron's textbook: Multiplayer Game Programming (2001)
//For this program, the comment test values are:
// server 6000
// client 198.168.0.1 6000
//I have tested other values however, and they work as well.

// ConnectionTest.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "SocketObject.h"
#include <errno.h>

//Function Prototypes
void vServerConnection( int iListenPort );
void vClientConnection( char *szServerIP, int iServerListenPort );

int main(int argc, char* argv[])
{

	//Debugging Information: Print out all passed in arguments
	//
	cout << "There are " << argc << " arguments:" << endl;
 	//Loop through each argument and print its number and value
	for(int nArg = 0; nArg < argc; ++nArg)
	{
		cout << nArg << " " << argv[nArg] << endl;
	}
	cout << endl;
	//

	//Check that enough arguments got passed in (minimum 2 plus the file name for a total of 3)
	if( argc < 3 )
	{
		//If not enough arguments were passed in display help
		cout << "----------------------------------------------------" << endl;
		cout << "               ConnectionTest Help                  " << endl;
		cout << "----------------------------------------------------" << endl;
		cout << "Usage: ConnectionTest [client/server] [ip,port/port]" << endl;
		cout << "" << endl;
		cout << "Example: ConnectionTest client 198.168.0.1 6000" << endl;
		cout << "" << endl;
		cout << "Example: ConnectionTest server 6000" << endl;
		cout << "" << endl;
		return( 0 );
	}
	
	//
	// If user selected server, listen on the given port 
	//
	if( !stricmp( argv[1], "server" ) )//stricmp() compares string regardless of case
	{
		vServerConnection( atoi( argv[2] ) );
	}
	//
	// User selected client, connect to given port and IP address
	//
	else
	{
		vClientConnection( argv[2], atoi( argv[3] ) );
	}

	/*
	Upon compleition of the use of Windows Sockets,
	the application or DLL must call WSACleanup to deregister
	itself from a Windows Sockets implementation and allow
	the implementation to free any resources allocated on behalf
	of the application or DLL.
	*/
	WSACleanup();
	
	return( 1 );
}

// Function for server
void vServerConnection( int iListenPort )
{
	SocketObject	ServerSocketObject;
	SocketObject	ClientSocketObject;
	//Data can be greater than 128 in length, it's just set to 128 for efficiency.
	//char			DataPacket[128];				// Data packet to receive//original version
	char			DataPacket[1024];				// Data packet to receive
	memset(DataPacket, 0, 1024);
	int				iBytesReceived = 0;				// # of bytes received
	
	cout << "<Server> Attempting to listen on Port " << iListenPort << endl;
	
	// Attempt to start the server
	if ( ServerSocketObject.Bind( iListenPort ) )
	{
		cout << "<Server> Listening" << endl;
		
		// Listen for connection on the Listen port, 
		ServerSocketObject.Listen();
		
		// Accept the connection
		ServerSocketObject.Accept( ClientSocketObject );
		cout << "<Server> Client Connected to Port " << iListenPort << endl;
		
		// Receive data
		//iBytesReceived = ClientSocketObject.Recv(&DataPacket[0], 128, 0);//original version
		iBytesReceived = ClientSocketObject.Recv(&DataPacket[0], 1024, 0);
		printf("%s\n", strerror(errno));
		cout << "<Server> Received " << iBytesReceived << " Bytes" << endl;
		cout << "<Server> Data Received = " << DataPacket << endl;

		// Disconnect the client
		ClientSocketObject.Disconnect();
		cout << "<Server> Client Disconnected" << endl;
	}
	else
	{
		cout << "<Server> Failed to Listen" << endl;
	}
}

// Function for client
void vClientConnection( char *szServerIP, int iServerListenPort )
{
	SocketObject	ClientSocketObject;
	char			DataPacket[128];		// Data packet to transmit
	int				iBytesSent = 0;			// # of bytes sent

	cout << "<Client> Connecting to " << szServerIP << ", Port " << iServerListenPort << endl;
	
	// Connect to the IP and Port 
	if( ClientSocketObject.Connect( szServerIP, iServerListenPort ) )
	{
		cout << "<Client> Connected" << endl;

		// Populate the data packet
		//strcpy(DataPacket, "TestData from Client");
		sprintf(DataPacket, "TestData from Client");
		//scanf("%s", &DataPacket);
		
		// Send data
		iBytesSent = ClientSocketObject.Send(DataPacket, 128, 0);
		cout << "<Client> Transmitted " << iBytesSent << " Bytes" << endl;
		
		// Disconnect from the server
		ClientSocketObject.Disconnect();
		cout << "<Client> Disconnected From Server" << endl;
	}
	else
	{
		cout << "<Client> Failed to Connect" << endl;
	}
}
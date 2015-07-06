//Here is the website where I learned all of this from:
//http://gafferongames.com/

//Why I chose UDP over TCP:
//http://gafferongames.com/networking-for-game-programmers/udp-vs-tcp/

//------------------------------
// File:		networkingp1.cpp
// Created:		2012/05/14
// Copyright:	Daniel Schenker
//------------------------------


#include "stdafx.h"

inline bool InitializeSockets()
{
#if PLATFORM == PLATFORM_WINDOWS
	WSADATA WsaData;
	return WSAStartup( MAKEWORD(2,2), &WsaData ) == NO_ERROR;
#else
	return true;
#endif
}

inline void ShutdownSockets()
{
#if PLATFORM == PLATFORM_WINDOWS
	WSACleanup();
#endif
}

int _tmain(int argc, _TCHAR* argv[])
{
	if(!InitializeSockets())
	{
		printf("ERROR: Could not initialize WSAStartup.\n");
		return false;
	}

	//=---Create a UDP socket---=

	int handle = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

	if ( handle <= 0 )
	{
		printf( "failed to create socket\n" );
		return false;
	}

	//=---Convert the address we want to send to into network notation---=

	//Starting form:
	//google.ca's ip address is 173.104.73.94
	unsigned int a = 127;
	unsigned int b = 0;
	unsigned int c = 0;
	unsigned int d = 1;
	//Special case: If you don't care what port your socket gets bound to just pass in "0" as your port, and the system will select a free port for you
	//Don’t use ports lower than 1024 because they are reserved for the system
	unsigned short port = 30000;//Random port I picked based on the tutorial's suggestions

	unsigned int destination_address = ( a << 24 ) | ( b << 16 ) | ( c << 8 ) | d;
	unsigned short destination_port = port;

	sockaddr_in address;
	address.sin_family = AF_INET;
	//address.sin_addr.s_addr = INADDR_ANY;
	address.sin_addr.s_addr = htonl( destination_address );//htonl() is the 32 bit version of htons() (hence l instead of s) (see next line's comment)
	//address.sin_port = htons( (unsigned short) port );//htons() converts a 16 bit integer value from host byte order (little or big-endian) to network byte order (big-endian)
	address.sin_port = htons( destination_port );

	//=---Bind UDP socket to a port number---=

	if ( bind( handle, (const sockaddr*) &address, sizeof(sockaddr_in) ) < 0 )
	{
		printf( "failed to bind socket\n" );
		return false;
	}

	//=---Set the socket as non-blocking---=
	#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
		int nonBlocking = 1;
		if ( fcntl( handle, F_SETFL, O_NONBLOCK, nonBlocking ) == -1 )
		{
			printf( "failed to set non-blocking socket\n" );
			return false;
		}
	#elif PLATFORM == PLATFORM_WINDOWS
		DWORD nonBlocking = 1;
		if ( ioctlsocket( handle, FIONBIO, &nonBlocking ) != 0 )
		{
			printf( "failed to set non-blocking socket\n" );
			return false;
		}
	#endif

	//=---Sending packets---=
	const int packet_size = 128;
	char pd[packet_size] = "TEST DATA";
	char* packet_data = &pd[0];

	printf("Data to send: %s\n", pd);

	int sent_bytes = sendto( handle, (const char*)packet_data, packet_size,
		0, (sockaddr*)&address, sizeof(sockaddr_in) );

	if ( sent_bytes != packet_size )
	{
		printf( "failed to send packet: return value = %d\n", sent_bytes );
		return false;
	}
	else
	{
		printf("Data Sent\n");
	}

	//=---Receiving packets---=
	while ( true )
	{
		unsigned char packet_data[256];
		unsigned int maximum_packet_size = sizeof( packet_data );

		#if PLATFORM == PLATFORM_WINDOWS
			typedef int socklen_t;
		#endif

		sockaddr_in from;
		socklen_t fromLength = sizeof( from );

		int received_bytes = recvfrom( handle, (char*)packet_data, maximum_packet_size,
			0, (sockaddr*)&from, &fromLength );
		/*int received_bytes = recvfrom( socket, (char*)packet_data, maximum_packet_size,
			0, (sockaddr*)&from, &fromLength );*/

		if ( received_bytes <= 0 )
			break;

		unsigned int from_address = ntohl( from.sin_addr.s_addr );
		unsigned int from_port = ntohs( from.sin_port );

		// process received packet
		printf("Data Received: %s\n", packet_data);

	}

	//Close Socket
	#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
    close( handle );
    #elif PLATFORM == PLATFORM_WINDOWS
    closesocket( handle );
    #endif
	/*#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
		close( socket );
	#elif PLATFORM == PLATFORM_WINDOWS
		closesocket( socket );
	#endif*/

	ShutdownSockets();

	return 0;
}
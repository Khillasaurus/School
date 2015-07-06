//Here is the website where I learned all of this from:
//http://gafferongames.com/

//Why I chose UDP over TCP:
//http://gafferongames.com/networking-for-game-programmers/udp-vs-tcp/

//------------------------------
// File:		networkingp2.cpp
// Created:		2012/05/14
// Copyright:	Daniel Schenker
//------------------------------

/*
Each time this program receives a packet,
it prints out which machine it came from,
and the size of the packet received.
*/

#include "stdafx.h"

int main( int argc, char* argv[] )
{
	//=---Iinitialize socket layer---=
	if( !InitializeSockets() )
	{
		printf( "failed to initialize sockets\n" );
		return 1;
	}
	
	//=---Create socket---=
	int port = 30000;
	
	printf( "creating socket on port %d\n", port );

	Socket socket;

	if ( !socket.Open( port ) )
	{
		printf( "failed to create socket!\n" );
		return 1;
	}

	//=---Send and receive packets to ourself until the user ctrl-breaks...---=
	while ( true )
	{
		const char data[] = "hello world!";

		socket.Send( Address(127,0,0,1,port), data, sizeof(data) );
			
		while ( true )
		{
			Address sender;
			unsigned char buffer[256]; 
			int bytes_read = socket.Receive( sender, buffer, sizeof( buffer ) );
			if ( !bytes_read )
			{
				break;
			}
			printf( "received packet from %d.%d.%d.%d:%d (%d bytes)\n", 
				sender.GetA(), sender.GetB(), sender.GetC(), sender.GetD(), 
				sender.GetPort(), bytes_read );
		}
		
		float seconds = 0.25f;
		Sleep( (int)(seconds * 1000.0f) );
		//wait( 0.25f );
	}
	
	//=---Shutdown socket layer---=
	
	ShutdownSockets();

	return 0;
}
# include "stdafx.h"

//Function Prototypes
void NetworkSetup();
void Receive(int);
void Send(int);

int _tmain(int argc, _TCHAR* argv[])
{	
	// a server
	//

	// one thread - listens for incoming connections
	// one thread per connection
	//

	NetworkSetup();

	// create server socket
	Uint32 mSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	// bind socket to a port
	// server address information
	struct sockaddr_in sa_server;
	memset(&sa_server, 0, sizeof(sa_server));
	sa_server.sin_family = AF_INET;
	sa_server.sin_addr.s_addr = INADDR_ANY/*inet_addr("172.31.227.140")*/;//replace with the value in cmd>ipconfig>ipv4
	sa_server.sin_port = htons(9000);

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
		}
	}

	// wait for a new connection
	fd_set is;//input set
	fd_set es;//error set
	fd_set ws;//write set
	int mHighFds = 0;//highest file descriptor socket

	struct timeval mMaxDelay;

	while(1)
	{
		dbPrintf("Waiting for connection...");

		// read set mask to zeroed before use
		FD_ZERO(&is);
		// read set mask to zeroed before use
		FD_ZERO(&es);
		// read set mask to zeroed before use
		FD_ZERO(&ws);

		// add sockets to 'select' set
		FD_SET(mSocket, &is);
		mHighFds = mSocket;

		mMaxDelay.tv_sec = 2;//how many seconds to block
		mMaxDelay.tv_usec = 0;//how many microseconds to block

		int rc = select(mHighFds + 1, &is, &ws, &es, &mMaxDelay);

		if(!rc)//if rc == 0
		{
			// everything is idle
		}
		else if(rc == SOCKET_ERROR)
		{
			// some kind of error
		}
		else
		{
			// something happened
			// a list of connections
			if(FD_ISSET(mSocket, &is))//if the file desriptor set has the socket in it
			{
				dbPrintf("connection received");

				// a new connection has arrived
				// accept
				int clientSocket;
				struct sockaddr_in addr;

				int addr_len;
				addr_len = sizeof(addr);
				clientSocket = accept(mSocket, (struct sockaddr *) &addr, &addr_len);
				if(clientSocket > 0)
				{
					// yay.. client is now connected
					unsigned char a;
					unsigned char b;
					unsigned char c;
					unsigned char d;

					// 0x0100007f	a
					// 0x000000ff
					// ----------
					// 0x0000007f

					// 0x0100007f	a
					// 0xff000000
					// 0x01000000
					//

					a = (addr.sin_addr.s_addr & 0x000000ff);		//mask off everything so I get just the first byte
					b = (addr.sin_addr.s_addr & 0x000000ff >> 8);
					c = (addr.sin_addr.s_addr & 0x000000ff >> 16);
					d = (addr.sin_addr.s_addr & 0x000000ff >> 24);

					dbPrintf("From (%08x) %d.%d.%d.%d", addr.sin_addr.s_addr, a, b, c, d);

						// recv
						Receive(clientSocket);

						// send
						Send(clientSocket);

						// disconnect
						closesocket(clientSocket);

				}
			}
		}
	}

	return 0;
}

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

void Receive(int socket)
{
	// recv()
	char recvBuffer[1024];
	memset(recvBuffer, 0, sizeof(recvBuffer));
	//int bytesRead = recv( mSocket, &recvBuffer[0], 1024, 0 );
	int bytesRead = recv( socket, &recvBuffer[0], 1024, 0 );

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
}

void Send(int socket)
{
	char sendBuffer[128];
	sprintf( sendBuffer, "Hello Remote Client" );

	//int byteswritten = send(mSocket, &sendBuffer[0], strlen(sendBuffer), 0);
	int byteswritten = send(socket, &sendBuffer[0], strlen(sendBuffer), 0);

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
}
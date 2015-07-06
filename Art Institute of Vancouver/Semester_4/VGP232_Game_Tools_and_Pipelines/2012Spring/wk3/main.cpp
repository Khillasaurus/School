// logtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "core/aierror.h"
#include "core/ailog.h"
#include <winsock2.h>
#include <Windows.h>
#include <process.h>

class Object
{
public:
	Object()
		:mVal(0)
	{
	}
	// pre
	Object& operator ++()
	{
		++mVal;// = (static_cast<Sint32>(InterlockedIncrement(reinterpret_cast<long volatile*>(&mVal))));
		return (*this);
	}
	// pre 
	Object& operator --()
	{
		--mVal;// = (static_cast<Sint32>(InterlockedDecrement(reinterpret_cast<long volatile*>(&mVal))));
		return (*this);
	}

	volatile Sint32 mVal;
};


unsigned int __stdcall myWorkerThread(void *arg)
{
	Object *pObj = (Object*)(arg);

	while(1)
	{
		++(*pObj);
		--(*pObj);
		dbPrintf("t: val is %d", pObj->mVal);
	}

	return 0;
}

void SaveBMP();


int _tmain(int argc, _TCHAR* argv[])
{
	SaveBMP();
	//lessonFirsthalf();

	// lessonSecondHalf();

	// ws2_32.lib

    WSADATA wsaData;
    int err;
    err = WSAStartup( MAKEWORD(2,0), &wsaData );
    if ( err == 0 )
    {
        //AILog( "cLGNetMan::InitTCPIP() %s,%s", wsaData.szDescription, wsaData.szSystemStatus );
        //sIsInitialized_TCPIP = true;
    }
    else
    {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
    }

	//TCPIP 
	// RAW
	// ICMP - eg ping
	// UDP - connectionless
	// TCP - connected, guaranteed ordering/delivery layer

	// sockets
	// open a socket


    // server address information
    // the port must be in network byte order.

    struct sockaddr_in sa_server;	
    sa_server.sin_family      = AF_INET;
    sa_server.sin_port        = htons( 80 );
    //sa_server.sin_addr.s_addr = inet_addr("173.194.73.94"); // google.ca's ip addr
	sa_server.sin_addr.s_addr = inet_addr("10.196.14.26"); // ai 'the hive' server

	Uint32 mSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if( mSocket != INVALID_SOCKET )
	{
	  if(connect( mSocket, (struct sockaddr *)&sa_server, sizeof(sa_server) ) != SOCKET_ERROR)
	  {
		  // yay.. we are connected!

		  // send()   "GET / HTTP/1.1\r\nUser-Agent: Mozilla/1.0\r\n\r\n"  == 0x0a0d
		  char sendBuffer[128];
		  //sprintf( sendBuffer, "GET / HTTP/1.1\r\nserver: www.google.ca\r\n\r\n" );
		  sprintf( sendBuffer, "GET / HTTP/1.1\r\nHost: thehive.artschool.com\r\nACCEPT: */*\r\nUSER_AGENT:aiclient/1.0 (Windows)\r\n\r\n");


            //req.Appendf("GET %s HTTP/1.1\r\n", pUrl);
            //req.Append("Accept: image/png, application/xaml+xml, */*\r\n");
            //req.Append("Accept-Language: en-ca\r\n");
            //req.Append("UA-CPU: x86\r\n");
            ////req.Append("Accept-Encoding: gzip, deflate\r\n");
            ////req.Append("User-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0; SLCC1; .NET CLR 2.0.50727; Media Center PC 5.0; .NET CLR 3.5.30729; .NET CLR 3.0.04506)\r\n");
            //req.Append("User-Agent: Clicktoy/1.0\r\n");
            //req.Appendf("Host: %s%s\r\n", pConnection->GetRemoteHostDef().GetHostName(), (pConnection->GetRemoteHostDef().mPort == 80 ? "" : ":port"));
            //req.Append("Connection: Keep-Alive\r\n");


	      int byteswritten = send( mSocket, &sendBuffer[0], strlen(sendBuffer), 0 );

		  if( byteswritten == SOCKET_ERROR )
		  {
		  }
		  else if( !byteswritten  )
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
}


// lesson
int lessonFirsthalf()
{

	dbPrintf("all done");

	Object myObj;

	_beginthreadex( NULL, (65535), myWorkerThread, &myObj, 0, NULL);


	while(1)
	{
		if( (++myObj).mVal <= 0 )
		{
			dbPrintf("1: val is <= 0 : %d", myObj.mVal);
		}

		if( (--myObj).mVal > 0 )
		{
			dbPrintf("2: val is <= 0 : %d", myObj.mVal);
			system("pause");
		}

		//demo only
		::Sleep(100);
	}

	return 0;
}



// a1 - due w4
// level generator
//
// generate a 2d map
//	- obstacle layer (trees/buildings/shrubbery/cars/rocks/ etc)
//	- treasure layer ( eggs, gold, silver, carrots, etc )
//  - spawn location layer (spawn type etc)

// - aggregate all layers into ...
// output single map file
//
// each layer is to be generated in a worker thread
// impl to your own discretion, a timer object.
// 65k x 65 k

// - hack visualizer
// - supply tool with x,y location, and output NxN grid as text output

void SaveBMP()
{
	FILE * f_out;   
	BITMAPFILEHEADER bh;
	BITMAPINFOHEADER bi;
	char file[260] = "test.bmp";
	class cPixel
	{
	public:
		cPixel()
			: b(0), g(128), r(0)
		{}
		char b;
		char g;
		char r;
	};

	int w = 640;
	int h = 480;

	cPixel img[ 307200 ] ;//[w * h ];
  
    // Open file   
	f_out = fopen(file, "wb");
    if ( f_out )    
	{
		bh.bfType =  (0x4D42) ;
		bh.bfSize = 307200;
		bh.bfReserved1 = 0;
		bh.bfReserved2 = 0;
		bh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

		// Write bmp file header   
		if (fwrite(&bh, 1, sizeof(BITMAPFILEHEADER), f_out) == sizeof(BITMAPFILEHEADER) )
		{
			bi.biSize = sizeof(BITMAPINFOHEADER);
			bi.biWidth = 640;
			bi.biHeight = 480;
			bi.biPlanes = 1;
			bi.biBitCount = 8;
			bi.biCompression = BI_RGB;
			bi.biSizeImage = 0; // or 307200
			bi.biXPelsPerMeter = 96;
			bi.biYPelsPerMeter = 96;
			bi.biClrUsed = 0;
			bi.biClrImportant = 0;


			// Write bmp info header   
			if (fwrite(&bi, 1, sizeof(BITMAPINFOHEADER), f_out) == sizeof(BITMAPINFOHEADER)) 
			{   
				cout<<"Error writing bitmap info header"<<endl;   
				//Write BMP data   
				for(int i=0; i<307200; i++) 
				{   
					fwrite(&img[i].b,1,1,f_out);    
					fwrite(&img[i].g,1,1,f_out);    
					fwrite(&img[i].r,1,1,f_out);   
				}   
				//for(j*=3; j%4!=0; j++) 
				//{
				//	fwrite(&zero,1,1,f_out); // Padding row to 4-byte multiple!    
				//}
			}   
			else
			{
				cout<<"Error opening file "<<file<<endl;   
			}
		}
		else
		{   
			cout<<"Error writing bitmap file header"<<endl;   
		}   
		fclose(f_out);  
	}
}
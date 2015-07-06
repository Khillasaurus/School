// wk1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include "sha1.h"
#include "md5.h"
#include <iostream>
using namespace std;



Uint32 CalcHash(const char *pKey)
{
    Uint32 len = 0;
    int c = 0;
    if( pKey )
    {
        len = strlen(pKey);
        c = (int)(*pKey);  
    }
    int val = 5381;  
	if( len )
	{
		while(len!=0)  
		{  
			//this is really odd, but it should give a good  
			//hash value, plus it is reasonably fast.  
			val = (val<<5) + val + c;  
			c = (int)*(++pKey);  
			--len;  
		}
	}
	else
	{
		val = 0;
	}
    return val;  
}


int _tmain(int argc, _TCHAR* argv[])
{

	// hashing 


	// simple
	Uint32 hash = CalcHash("this is a string of data");


	// SHA1
	SHA1 sha1;
	sha1.Reset();
	sha1.Input("abcd", 4);
	// store digest as 20 bytes (5 ints)
	// 12345678901234567890
	Uint32 sha1Digest[5];
	sha1.Result( sha1Digest );
	//as a string...
	// convert 20 bytes into..
	//eg:  40 bytes, each byte == 2 hex characters
	//"0102030405cd .... "


	// md5
	cMD5Hash md5;
	md5.MD5Init();
	Uint8 in[5] = {"abcd"};
	md5.MD5Update( in, 4 );
	Uint8 digest[16];
	md5.MD5Final( digest );

	return 0;
}




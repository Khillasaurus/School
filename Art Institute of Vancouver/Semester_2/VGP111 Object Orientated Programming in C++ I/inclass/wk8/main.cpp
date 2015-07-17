#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common/vgptime.h"
#include "common/vgptimer.h"
#include <vector>
#include <list>
#include <map>
#include <assert.h>
#include <crtdbg.h>

int _tmain(int argc, _TCHAR* argv[])
{
	char name[16];

	sprintf( name, "ken" );
	//or
	strcpy( name, "ken" );
	//or
	strcat( name, "ken" );

	//changecase
	for( int i = 0; i < strlen(name); ++i )
	{
		//lower
		name[i] = _tolower( name[i] );
		//upper
		name[i] = _toupper( name[i] );
	}

	//find
	char* p = strstr( name, "ken" );

	//compare
	int val = strcmp( name, "ken" );

	cAIString mystring1;
	mystring1 = "ken";
	cAIString mystring2(ken);
	cAIString mystring3(mystring1);
	cAIString mystring4 = mystring2;

	//internally the string's actual storage is empty
	cAIString mystring5(anAllocationSize);
	
	if( mystring1 == mystring2 )
	{
	}

	if( mystring1.Find(mystring2) ||
		mystring1.Find("ken") ||
		mystring1.Find('k') )
	{
	}

	if( mystring1.rFind(mystring2) )
	{
	}

	int idx = mystring1.Find( 'e' );
	//result == "en"
	cAIString sub1 = mystring1.Substring( idx, cAIString::kEndOfString );
	//result == "ke"
	cAIString sub1 = mystring1.Substring( cAIString::kStartOfString, idx );
	//result == "k"
	cAIString sub1 = mystring1.SubString( cAIString::kStartOfString, idx - 1 );

	unsigned int hash = mystring1.GetHash();

	//append
	mystring1 += mystring2;

	mystring1 << 1;
	mystring1 << "james";

	mystring1.Trim(); //remove leading "whitespace" == spaces, tabs, crlf
	mystring1.rTrim(); //remove tailing "whitespace" == spaces, tabs, crlf
	
	system( "pause" );

	return 0;
}





struct x
{
	x(int len)
	{
		int tlen = _len << 7 / 8;
		p = new char [_len];
		len = _len;
		dlen = 0;
	}
	append( char* pd, int _len )
	{
		if( len - dlen < _len )
		{
			//append
		}
		else
		{
			char* pold = p;
			p = new char[ len + _len ];
			memcpy( p , pold, dlen );
			//append pd
			delete pold;
		}
	}
	char* p;
	int len;
	int dlen;
};
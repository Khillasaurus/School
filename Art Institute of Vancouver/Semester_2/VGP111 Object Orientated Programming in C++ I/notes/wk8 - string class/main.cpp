//

#include "stdafx.h"
#include <Windows.h>
#include "common/vgptime.h"
#include "common/vgptimer.h"
#include <vector>
#include <list>
#include <map>
#include <assert.h>
#include <crtdbg.h>


void mybuddy(const cAIString &mystring);


std::string;
std::wstring;

char c[10]; // == 1 bytes
wchar_t wc[10]; // == 2 bytes

c = "apple";
wc = _T("apple");
wc = _TEXT("apple");
wc = L"apple";

(char*)wc = "a\0p\0p\0l\0e\0" + \0;

WCharToUTF8()
UTF8ToWChar()


class cAIString
{
public:
	friend void mybuddy(const cAIString &mystring);

	friend ostream &operator <<(ostream &stream, const cAIString &mystr );

	friend bool compare(const cAIString &mystrm, const cAIString &mystr2 );

	friend class cAIBuffer;
private:
	char buf[10];
private:
	char buf2[10];
};



bool compare(const cAIString &mystrm, const cAIString &mystr2 )
{
	return (strcmp( mystrm.buf, mystr2.buf) == 0);
}

if( mystrm.compare(mystr2) )
{
}

if( compare( mystrm, mystr2 ) )
{
}

ostream &operator <<(ostream &stream, const cAIString &mystr )
{
	stream << mystr.buf;
	return stream;
}

void mybuddy(const cAIString &mystring)
{
	mystring.buf; //!!no
}

cout << mystring << mystring;



int _tmain(int argc, _TCHAR* argv[])
{
	char name[16];

	// set value

	sprintf(name,"ken");
	//or
	strcpy(name,"ken");
	//or
	strcat(name,"ken");

	// changecase
	for(int i = 0; i < strlen(name); ++i)
	{
		// lower
		name[i] = _tolower(name[i]);
		// upper
		name[i] = _toupper(name[i]);
	}
	
	// find
	char *p = strstr(name,"ke");
	// compare
	int val = strcmp(name,"ken");

	cAIString mystring1;
	mystring1 = "ken";
	cAIString mystring2("ken");
	cAIString mystring3(mystring1);
	cAIString mystring4 = mystring2;

	printf("%s", name);
	TCHAR x;
	
	std::wstring yuck;
	yuck = L"yucky";

#if defined(_UNICODE)
	printf("%s", yuck.c_str() );
#else
	printf("%S", yuck.c_str() );
#endif

	printf("%s", mystring1.ToString() );
	printf("%s", mystring1.AsCStr() );

	// internally, the string's actual storage is empty
	cAIString mystring5(anAllocationSize); 

	if( mystring1 == mystring2 )
	{
	}

	if( mystring1.Find( mystring2 ) ||
		mystring1.Find( "ken" ) ||
		mystring1.Find( 'k' )  )
	{
	}
	if( mystring1.rFind( mystring2 ) )
	{
	}

	int idx = mystring1.Find( 'e' );
	// result == "en"
	cAIString sub1 = mystring1.SubString( idx, cAIString::kEndOfString );
	// result == "ke"
	cAIString sub1 = mystring1.SubString( cAIString::kStartOfString, idx );
	// result == "k"
	cAIString sub1 = mystring1.SubString( cAIString::kStartOfString, idx - 1 );

	unsigned int hash = mystring1.GetHash();

	// append
	mystring1 += mystring2;
	mystring1 += " a string ";

	mystring1 << 1;
	mystring1 << "james";

	mystring1.Trim(); // remove leading "whitespace" == spaces, tabs, crlf
	mystring1.rTrim(); // remove tailing "whitespace" == spaces, tabs, crlf

	system("pause");
	
	return 0;
}




struct x
{
	x(int _len)
	{
		int tlen = _len << 7 / 8;
		p = new char [_len + padding];
		len = _len;
		dlen = 0;
	}
	append(char *pd, int _len)
	{
		if( len - dlen < _len )
		{
			// append [d
		}
		else
		{
			char *pold = p;
			p = new char[ len + _len + padding ];
			memcpy( p, pold, dlen );
			// append pd
			delete pold;
		}
	}
	char *p;
	int len;
	int dlen;
};









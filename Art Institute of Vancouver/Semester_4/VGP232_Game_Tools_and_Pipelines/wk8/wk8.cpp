//-----------------------------
// File:		wk8.cpp
// Created:		2012/05/23
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"

//Function Prototypes
Uint32 CalcHash(const char*);
Uint32 CalcHash(const char*, Uint32);

class cAssetKey
{
	Uint32 mHash;
#if DEBUG
	char mName[128];
#endif
};

int _tmain(int argc, _TCHAR* argv[])
{
	Uint32 hash = CalcHash("./models/astroboy.png");
	///cNPC = *pNPC;

	cout << "hash = " << hash << endl;
	return 0;
}

Uint32 CalcHash(const char* pKey)
{
	if(pKey)
	{
		return CalcHash(pKey, strlen(pKey));
	}
	return 0;
}

Uint32 CalcHash(const char* pKey, Uint32 len)
{
	int c = 0;
	int val = 5381;
	if(pKey && len)
	{
		c = (int)(*pKey);
		while(len)
		{
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


///Notes:
/*
//"abcd" -> 4738
//"dcba" -> 8345
//"Abcd" -> 1823

'a' == 0x61 == 11000001
rot 5
111000
56
'8'
*/
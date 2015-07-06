//====================================================================================================
//File:			main.cpp
//Created:		2012/09/01
//Copyright:		Daniel Schenker
//Description:		Defines the entry point for the console application.
//====================================================================================================

//====================================================================================================
//Includes
//====================================================================================================

//Precompiled headers
#include "stdafx.h"

#include <iostream>
#include <deque>
#include <time.h>

using namespace std;

//====================================================================================================
//Main
//====================================================================================================

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	deque<int> mBits;

	bool foundSame = false;
	int mask = 0;
	int count = 0;

	while(1)
	{
		int newnum = rand() % 255; //new seed
		cout << "Number = " << newnum << endl;
		for(int i = 1; i <= 6; ++i)
		{
			int num = newnum;
			while(!foundSame)
			{
				int xor = (num >> 7) ^ (num >> (7-i));	//xor
				num = (num << 1) | xor;
				num &= ~(1 << 8);
				for(int j = 0; j < (int)mBits.size(); ++j)
				{
					if(mBits[j] == num)
					{
						foundSame = true;
					}
				}
				if(!foundSame)
				{
					mBits.push_back(num);
					count++;
				}
				else
				{
					printf("Comparing with Bit %d,\t count Rate = %d \n",i , count);
					count = 0;
					mBits.clear();
				}
			}
			num = newnum;
			foundSame = false;
		}
	}

	return 0;
}
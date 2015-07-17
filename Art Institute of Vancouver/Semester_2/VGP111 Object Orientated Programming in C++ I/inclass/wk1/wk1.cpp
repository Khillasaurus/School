// wk1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>


int _tmain(int argc, _TCHAR* argv[])
{


	
	bit								0 or 1
	nibble							4 0s or 1s
	byte / char						8 bits
	word / short					16 bits
	long / dword / int / size_t		32 bits
	float							32 bits
	double							64 bits
	long long int / __int64			64 bits
	__int128						128 bits

	0000 0000 0000 0000   0000 0000 0000 0000

	lvalue; theanswer
	rvalue; 5

	0x00000000; //address 0

	unsigned int memory;
	unsigned int *pMemory;
	register;	//allows you to store things explicitly into a register (important variable, must run fast) (not really seen in use anymore since programs are bigger now and computers are much faster)
	signed;		//explicit declaration

	mutable const int kMaxTime = 5; //can now change that constant

	if( endofworld )
	{
		if( time < kMaxTime )
		{
			OnLotsOfTime();
		}
		else
		{
			orint("no worries");
			NoTime();
		}
	}

	enum eUnitTypes
	{
		kTank,				//0
		kJet,				//1
		kSoldier = 55,		//55
		kBoat,				//56
		kGeneral,			//57
		kCadet = -2;		//-2
		kLieutenant,		//-1
		kTruck				//0		be careful with enum having funny values, it's ok but be careful
	};

	enum eFlags
	{
		kRead = 0x00000001,
		kWrite= 0x00000002,
		kDelete= 0x00000004 //do not have trailing comma even though it may work with it sometimes
	};

	int bit = 0x00000001;

	int a;
	int b;
	
	//useful in matrices
	union
	{
		int a;
		char b;
	} stuff;

	stuff.a = 0xffffffff;
	stuff.b == ff;

	union
	{
		float x;
		float y;
		float z;
		float q;
		float m[4];
	} moreStuff;


	int unit = GetUnitType();

	mutable const int kSatellite = 6; //needs to be const, but may be mutable (very bad programming)

	switch( unit )
	{
	case kSatellite;
		{
			int i = l;
		}
		break;

	default;
		//noop
		break;
	}

	//switch is slightly more efficient than if else if statements
	//never have switches inside of switches because it looks horrible


	mutable;
	volatile; //means it can change

	for( int i = 0; i < 5; ++i )
	{
		//pMemory = (unsigned int*)malloc( sizeof(unsigned int) );
		pMemory = reinterpret_cast<unsigned int*>( malloc( sizeof(unsigned int) ) );
	}

	free(pMemory);

	stack;
	a program is given a block of memory for it to scribble in which is its stack
	heap;


	char letter;

	letter = 'c';

	return 0;

	
	//only reasonable use for goto
	FILE *fp = fopen("thefile.txt");
	if( fp )
	{
		//alloc memory
			goto error;
		//load file
		//init mouse
		//open comport
	}

	:error
		fclose(fp);
		if( pMemory )
		{
		
		}
	close(comport);



}


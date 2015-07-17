// wk1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "monster.h"
#include "hero.h"
#include "Windows.h"

namespace vgp
{
	const float kPI = 3.1459653f;
}

//public
////protected
////private
//struct stats	//defaults public
//{
//	void Buff();
//	Uint32 strength;
//	Uint32 dexterity;
//	Uint32 intelligence;
//};
//
//void stats::Buff()
//{
//	strength *= 10;
//}

						//class cCharacter; //same as struct but private
						//{
						//public:
						//	void Buff();
						//
						//private:
						//	Uint32 strength;
						//	Uint32 dexterity;
						//	Uint32 intelligence;
						//};
						//
						//class cMonster : public cCharacter	//almost always public, if not explain why to yourself so you don't get confused
						//{
						//public:
						//	void Yell();
						//};
						//
						//void cMonster::Yell()
						//{
						//	cout << "aaaaaaaugh" << endl;
						//}
						//
						//class cHero : public cCharacter	//almost always public, if not explain why to yourself so you don't get confused
						//{
						//public:
						//	void Yell()
						//	{
						//		cout << "RAAAAAGHHH" << endl;
						//	}
						//};

// -------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	cMonster zombie;
	zombie.Buff();

	cHero hero;
	hero.Buff();

	zombie.Yell();
	hero.Yell();

	SYSTEMTIME stStart;
	SYSTEMTIME stNow;

	GetSystemTime(&stStart);

	cout << "Date: " << stStart.wYear << "/" << stStart.wMonth << "/" << stStart.wDay << endl;
	cout << "Time: ";
	cout.fill('0');
	cout.width(2);
	cout << stStart.wHour << "/";
	cout.fill('0');
	cout.width(2);
	cout << stStart.wMinute << "/";
	cout.fill('0');
	cout.width(2);
	cout << stStart.wSecond << "/";
	cout.fill('0');
	cout.width(3);
	cout << stStart.wMilliseconds << endl;

	Uint32 now = stStart.wMinute * 60 * 1000 + stStart.wSecond * 1000 + stStart.wMilliseconds;
	Uint32 stopTime = now + 1000;

	while( now < stopTime )
	{
		GetSystemTime(&stNow);
		
		now = stNow.wMinute * 60 * 1000 + stNow.wSecond * 1000 + stNow.wMilliseconds;
	}

	//stats playerStats;

	//playerStats.strength = 12;
	//playerStats.Buff();


	//Uint32 i = 0x10000002;

	//printf("Hi\n");

	////getchar();	//blocking buffered single character
	////getch();		//blocking unbiffered single char
	////gets();
	////scanf();

	////stdout
	////stderr
	//// file / socket ...

	//std::cout << "Hello" << std::endl;	//much better this way than
	//cout << vgp::kPI << endl;			//this way

	////why printf looks better sometimes in cases such as the following
	//printf("%8.5f\n", 1.01f);	//f at end because 1.01 defaults to double, this way makes it a float
	//cout << "i=" << i << endl;
	//cout.width(10);
	//cout.precision(10);
	//cout << 1.01f << endl;


	return 0;
}




// ASSIGNMENT
// turn stStart and stNow into cTime objects
// determine an elapsed time (as a cTime) from the above two cTimes

//ai@clicktoy.com
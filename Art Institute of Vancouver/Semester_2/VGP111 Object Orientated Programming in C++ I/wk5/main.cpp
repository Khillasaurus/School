// wk1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"
#include "common/vgptime.h"
#include "common/vgptimer.h"

void TimerCode();

// -------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	vector<Uint32> numbers;

	// reserve space for this number of elements
	numbers.reserve(40);

	// there is now only one element in the vector
	numbers.push_back( 1 );

	// make the vector contain this number of elements
	numbers.resize(40);

	cout << "First List" << endl;

	for( Uint32 i = 0; i < numbers.size(); ++i )
	{
		printf("%d\n", numbers[i] );
		cout << numbers[i] << endl;
	}

	cout << "Resized List" << endl;

	vector<Uint32>::iterator it;
	for( it = numbers.begin(); it != numbers.end(); ++i )
	{
		printf("%d\n", (*it) );
		cout << (*it) << endl;
	}

	////
	list<Uint32> numList;

	typedef list<Uint32> tNumList;
	typedef tNumList::iterator tNumIter;

	tNumList numListl
	
	numList.push_back(2);

	tNumListIter it1;
	for( it1 = numbers.begin(); it1 != numbers.end(); ++i )
	{
		printf("%d\n", (*it1) );
		cout << (*it1) << endl;
	}

	numList.sort();

	cout << "list - sorted asc" << endl;

	tNumListIter it1;
	for( it1 = numList.begin(); it1 != numList.end(); ++i )
	{
		printf("%d\n", (*it1) );
		cout << (*it1) << endl;
	}

	numList.sort( greater<int>() );

	tNumListIter it1;
	for( it1 = numList.begin(); it1 != numList.end(); ++i )
	{
		printf("%d\n", (*it1) );
		cout << (*it1) << endl;
	}

	class cRacer
	{
	public:
		cRacer(const char* _name, Uint32 _num)
		: mNumber(_num)
		{
			strcopy(mName,_name);
		}

		// comparison
		bool operator<(const cRacer &rhs)
		{
			return (mNumber < rhs.mNumber);
		}
		// cast obj to a number
		/*operator int()
		{
			return mNumber;
		}*/

		char mName[16];
		Uint32 mNumber;
	};
	list< cRacer > racers;

	racers.push_back( cRacer("James",2) );
	racers.push_back( cRacer("Ken",1) );
	racers.push_back( cRacer("Daniel",17) );

	list< cRacer >::iterator racerIter;
	for( racerIter = racers.begin(); racerIter != racers.end(); ++racerIter )
	{
		cout << (*racerIter).mName << ":" << (*racerIter).mNumber << endl;
	}

	racers.sort();
	for( racerIter = racers.begin(); racerIter != racers.end(); ++racerIter )
	{
		cout << (*racerIter).mName << ":" << (*racerIter).mNumber << endl;
	}

	racers.insert( cRacer("Michael C",88 ) );
	//racers.insert( racers.begin(), cRacer("Michael C",88 ) );

	cout << "racer map" << endl;

	map< Uint32, cRacer > racerMap;

	racerMap.insert( map< Uint32, cRacer>::value_type( 1, cRacer("Daniel", 17) ) );

	map< Uint32, cRacer >::iterator mapIter;
	for( mapIter = racers.begin(); mapIter != racers.end(); ++mapIter )
	{
		cout << (*mapIter).second.mName << ":" << (*mapIter).second.mNumber << endl;
	}

	// poker or blackjack
	// build a deck out of "card" objects
	// deal random hand(s) to player(s)
	// all cards are new'd
	// deck & hands use stl containers
	// hand must be sorted according to card value
	// hand should print readable card values "ace of spades" etc
	// value the hand(s) & declare winner


	return 0;
}

void TimerCode()
{

	cTime stopTime(0,0,1);
	cTime clock; //0, 0, 0
	cTime frameTime(0,0,0,32); //32 frames per second
	cTimer timer;
	timer.Start();

	Uint32 tickCounter = 0;

	while( clock < stopTime )
	{
		++tickCounter;
		cTime elapsed = timer.GetElapsed();
		if( elapsed >= frameTime )
		{
			cTimer workTimer;
			workTimer.Start();

			clock.Add( elapsed.CalcSum() );
			clock.ToString();
			cout << "tick = " << tickCounter << endl;
			tickCounter = 0;

			workTimer.Stop();

			timer.Start();

		}
	}

	cout << "Time is up!" << endl;
	
}
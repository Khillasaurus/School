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


	class cRacer
	{
	public:
		cRacer(const char* _name, Uint32 _num)
		: mNumber(_num)
		{
			//mpName = new char(strlen(_name));
			strcpy(mName,_name);
		}

		// 
		//bool operator<(const cRacer &rhs)
		//{
		//	//return (mNumber < rhs.mNumber);
		//	return (_stricmp(mName,rhs.mName) < 0 );
		//}
		// cast obj to an int
		operator int()
		{
			return mNumber;
		}

		char mName[16];
		Uint32 mNumber;
	};

//! ---------------

int _tmain(int argc, _TCHAR* argv[])
{
	//vector : sequential, proximal, fast for indexed ops, slower for random inserts
	//list : fast traversal, fast inserts, non-proximal
	//map : tree, key->value storage, fast retrieval, sorted on insert
	//queue
	//dequeue
	//multimap
	//set
	
	vector<Uint32> numbers;

	// reserve space for this number of elements
	numbers.reserve(40);

	// there is now only one element in the vector
	numbers.push_back( 1 );

	cout << "first vector" << endl;

	for( Uint32 i = 0; i < numbers.size(); ++i )
	{
		//printf("%d\n", numbers[i] );
		cout << numbers[i] << endl;
	}

	// make the vector contain this number of elements
	numbers.resize(40);

	cout << "resized vector" << endl;

	vector<Uint32>::iterator it;
	for( it = numbers.begin(); it != numbers.end(); ++it )
	{
		//printf("%d\n", (*it) );
		cout << (*it) << endl;
	}


	//// 
	cout << "list" << endl;

	typedef list<Uint32> tNumList;
	typedef tNumList::iterator tNumListIter;

	tNumList numList;

	numList.push_back(2);
	numList.push_back(4);
	numList.push_back(2);

	tNumListIter it1;
	for( it1 = numList.begin(); it1 != numList.end(); ++it1 )
	{
		//printf("%d\n", (*it) );
		cout << (*it1) << endl;
	}

	numList.sort();

	cout << "list - sorted asc" << endl;

	for( it1 = numList.begin(); it1 != numList.end(); ++it1 )
	{
		//printf("%d\n", (*it) );
		cout << (*it1) << endl;
	}

	numList.sort( greater<int>() );

	cout << "list - sorted dsc" << endl;
	for( it1 = numList.begin(); it1 != numList.end(); ++it1 )
	{
		//printf("%d\n", (*it) );
		cout << (*it1) << endl;
	}


	list< cRacer > racers;

	racers.push_back( cRacer("James",2) );
	racers.push_back( cRacer("ken",1) );
	racers.push_back( cRacer("Daniel",37) );
	racers.push_back( cRacer("Alex",50) );
	racers.push_back( cRacer("Jordan",5) );
	racers.push_back( cRacer("Michael",17) );

	cout << "racers - raw" << endl;

	list< cRacer >::iterator racerIter;
	for( racerIter = racers.begin(); racerIter != racers.end(); ++racerIter )
	{
		cout << (*racerIter).mName << ":" << (*racerIter).mNumber << endl;
	}

	racerIter = racers.begin();
	racers.insert( racerIter, cRacer("Michael C",88) );

	cout << "racers - sorted" << endl;
	racers.sort();

	for( racerIter = racers.begin(); racerIter != racers.end(); ++racerIter )
	{
		cout << (*racerIter).mName << ":" << (*racerIter).mNumber << endl;
	}



	cout << "racer map" << endl;

	typedef map< Uint32, cRacer > tRacerMap;
	typedef tRacerMap::iterator tRacerMapIter;
	typedef tRacerMap::value_type tRacerMapData;
	tRacerMap racerMap;

	cRacer alex("Alex",50);
	racerMap.insert( tRacerMapData( alex.mNumber, alex ) );

	//racerMap.insert( pair<Uint32, cRacer>( 5, cRacer("Jordan",5) ) );

	tRacerMapIter mapIter;
	for( mapIter = racerMap.begin(); mapIter != racerMap.end(); ++mapIter )
	{
		cout << (*mapIter).second.mName << ":" << (*mapIter).second.mNumber << endl;
	}

	cout << "search for alex" << endl;
	mapIter = racerMap.find( 50 );
	if( mapIter != racerMap.end() )
	{
		// i found it!
		cout << (*mapIter).second.mName << ":" << (*mapIter).second.mNumber << endl;

		//delete (*mapIter).second;
		//racerMap.erase( mapIter );
	}

	racerMap.clear();


	int *q0 = (int *)malloc( sizeof(int) );
	free(q0);


	int *q0b = (int *)malloc( sizeof(int) * 10 );
	free(q0b);


	int *q1 = new int;
	delete q1;


	int *q2 = new int[10];
	delete [] q2;

	class foo
	{
	public:
		foo()
			: mIsInitialized(false)
			,	mNumber(0)
		{
			static Uint32 sInsId = 0;
			mNumber = sInsId++;
			printf("Create foo instance: %d\n", mNumber );
		}
		~foo()
		{
			//_ASSERT(!mIsInitialized);
			//Purge();
			printf("Create foo instance: %d\n", sInsId++ );
		}
		bool Init()
		{
			if( !mIsInitialized )
			{
				//fh = fopen("somefile.txt","r");
				mIsInitialized = true;
			}
			return ( mIsInitialized );
		}
		bool Purge()
		{
			if( !mIsInitialized )
			{
				//fclose(fh);
				mIsInitialized = false;
			}
			return (!mIsInitialized);
		}
		bool mIsInitialized;
		int mNumber;
		FILE *fh;
	};

	foo *pFoo = new foo();
	if( pFoo )
	{
		if( pFoo->Init() )
		{
			// use it

			pFoo->Purge();
		}

		delete pFoo;
	}

	int x = 1;
	
	foo *foos = new foo[10]
	delete [] foos;

	// poker or blackjack
	// build a deck out of "card" objects
	// deal random hand(s) to player(s)
	// all cards are new'd
	// deck & hands use stl containers
	// hand must be sorted according to card value
	// hand should print readable card vales "ace of spades" etc
	// value the hand(s) & declare winner

	return 0;
}


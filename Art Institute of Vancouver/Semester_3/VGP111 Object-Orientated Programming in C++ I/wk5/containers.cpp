//-----------------------------
// File:		main.cpp
// Created:		2012/2/3
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "vgp/vgptime.h"
#include "vgp/vgptimer.h"
#include <list>
#include <vector>
#include <algorithm>
#include <map>

struct cNode
{
	cNode(int _x)
	:	mpPrev(NULL)
	,	mpNext(NULL)
	,	x(_x)
	{
	}

	cNode *mpPrev;
	cNode *mpNext;

	int x;
};

void LessonWeek5b()
{

	cNode theRoot(1);
	cNode firstChild(2);

	theRoot.mpNext = &firstChild;
	firstChild.mpPrev = &theRoot;
	
	cNode *pList;

	//iterate forwards
	pList = &theRoot;
	while(pList)
	{
		cout << "x = " << pList->x << endl;
		pList = pList->mpNext;
	}

	//iterate backwards
	pList = &firstChild;
	while(pList)
	{
		cout << "x = " << pList->x << endl;
		pList = pList->mpPrev;
	}

	cout << "-- yay --" << endl;



	//start here with standard template library

	//start here with lists
	//lists are far better for sorting than vectors

	std::list<int> myList;
	std::list<int>::iterator it;

	myList.insert(myList.end(), 1);
	myList.insert(myList.end(), 5);
	myList.insert(myList.end(), 3);
	myList.insert(myList.end(), 6);

	cout << "Unsorted" << endl;
	for(it = myList.begin(); it !=myList.end(); ++it)
	{
		cout << "value = " << (*it) << endl;
	}

	cout << "Sorted" << endl;
	myList.sort();
	for(it = myList.begin(); it !=myList.end(); ++it)
	{
		cout << "value = " << (*it) << endl;
	}

	cout << "-- yay --" << endl;


	//start here with vectors

	std::vector<int> myVector;
	std::vector<int>::iterator vecIt;

	//myVector.reserve(2);	//eg int numbers[2];
	myVector.push_back(1);	//eg numbers[0] = 1
	myVector.push_back(5);	//eg numbers[1] = 5
	myVector.push_back(3);	//eg numbers[2] = 3
	myVector.push_back(7);	//eg numbers[3] = 7

	cout << "index of for loop" << endl;
	for(int i = 0; i < (int)myVector.size(); ++i)
	{
		cout << "value = " << (myVector[i]/*index of is nano seconds faster than iterators so the time saved is almost useless*/) << endl;
	}

	cout << "iterator for loop, as well as sorted" << endl;
	sort(myVector.begin(), myVector.end());
	for(vecIt = myVector.begin(); vecIt !=myVector.end(); ++vecIt)
	{
		cout << "value = " << (*vecIt)/*iterator i was talking about in above inline comment*/ << endl;
	}

	//deque, queue, stack
	//will talk about later

	//map (also known as hastable in things like java)
	
	//ugly way
	//std::map<int, std::string> myMap;
	//std::map<int, std::string>::iterator mapIt;
	//
	//myMap, insert( std::map<int, std::string>::value_type(1, "ken"));

	typedef std::map<int, std::string> tMyMap;
	typedef tMyMap::iterator tMyMapIt;
	typedef tMyMap::value_type tMyMapData;

	tMyMap myMap;
	tMyMapIt mapIt;

	myMap.insert(tMyMapData(1, "ken"));
	myMap.insert(tMyMapData(5, "daniel"));
	myMap.insert(tMyMapData(2, "joseph"));
	myMap.insert(tMyMapData(7, "justin"));
	for( mapIt = myMap.begin(); mapIt != myMap.end(); ++mapIt)
	{
		std::cout <<
			"key = " << (*mapIt).first << "\t" << //normally you don't print key, this is just for learning's sake
			"value = " <<(*mapIt).second.c_str() << endl;
	}

	mapIt = myMap.find( 5 );
	if( mapIt != myMap.end())
	{
		cout << "Yay found it!" << endl;
	}

}

	/*
	assignment	Game of WAR

	create a deck of card objects (eg clsas Card)
	deck of 52 objects
	create two player objects
	players draw a card (or have it dealt to them)
	implement WAR rules... tie... draw 3... etc
	declare winner of each hand
	declare winner of game
	all cards, players etc objects... are allocated from heap (aka cCard *pCard = new cCard())

	lists are probably easier than vectors for this assignment


	//the following two are the same but the second is prefereable as you do not create a temporary storage
	cCard *pCard = new cCard();
	myVector.push_back(pCard);

	//there is a random shuffle function but i have to find it myself if i want to use it

	list<int*>ptrList;
	ptrList.push_back(new int);
	ptrList.push_back(new int);
	ptrList.push_back(new int);
	ptrList.push_back(new int);

	int* p = ptrList.back();
	ptrList.pop;
	//ptrList.erase(iterator);//this is an alternate method so I probably won't use it until I understand it better

	for(+it = ptrList.begin(); it != ptrList.end(); +it)
	{
		delete (*it);
	}
	ptrList.clear();


	*/
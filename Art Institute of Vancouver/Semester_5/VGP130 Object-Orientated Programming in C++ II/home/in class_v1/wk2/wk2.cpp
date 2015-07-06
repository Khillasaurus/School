//-----------------------------
// File:		main.cpp
// Created:		2012/07/12
// Copyright:	Daniel Schenker
//-----------------------------


#include "stdafx.h"
#include <queue>
using namespace std;

int add(int a, int b)
{
	return a + b;
}

int float(float a, float b)
{
	return a + b;
}

template<typename T>
T add(T a, T b)
{
	return a + b;
}


class cThing
{
	cThing operator +(const cThing &rhs)
	{
		cThing tmp;
		tmp.x = x + rhs.x;
		return tmp;
	}
};


class cEvent
{
public:
	int mId;
};

class cEventMan
{
	void AddEvent();
	queue<cEvent*> msgQ;
}



int _tmain(int argc, _TCHAR* argv[])
{
	cEventMan eventMan;

	while(1)
	{
		eventMan.Update();
		//simulator.Update();
		//renderer.Update();
		//userinterface.Update()
		//{
			//if(mouse.isbuttonpressed(kLEFTButton)
			//{
			//	//play
			//}
		}
	}
	
	queue<cEvent*> msgQ;

	//create and post and event...
	cEvent* pEvt = new(cEvent(1);
	msgQ.push(pEvt);

	while(1)
	{
		if(!msgQ.empty())
		{
			pEvt = msgQ.front();
			msgQ.pop();
		}
		if(pEvt)
		{
			switch(pEvt->mId)
			{
			case 1:
				{
				//received event id == 1
				cEvent* pTmpEvt = new(cEvent(2);
				msgQ.push(pTmpEvt);
				}
				break;
			}
			delete pEvt;
		}
	}



	int result = add<int>(1, 1);

	cThing thingResult = add<cThing>(cThing(), cThing());

	return 0;
}
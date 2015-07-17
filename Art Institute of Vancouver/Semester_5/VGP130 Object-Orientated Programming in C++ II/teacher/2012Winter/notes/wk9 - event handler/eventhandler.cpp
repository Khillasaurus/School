// ------------------------------------------
// Filename:	wk9.cpp
// Created:		2012/03/02
// Copyright 2012 me
// ------------------------------------------

#include "stdafx.h"
#include "eventhandler.h"

// ------------------------------------------

cEventHandler::cEventHandler()
{
}

// ------------------------------------------

bool cEventHandler::HandleEvents()
{
	Uint32 count = mEvents.size();
	//while( !mEvents.empty() )
	while( count )
	{
		//Lock()
		Uint32 eventId = mEvents.front();
		mEvents.pop();
		//UnLock();
		--count;

		//version 1
		//for(Uint32 i = 0; i < mEventTargets.size(); ++i)
		//{
		//	mEventTargets[i]->OnEvent( eventId );
		//}

		//version 2
		tEventTargetMapRangeIter rangeIt;
		tEventTargetMapIter it;
		rangeIt = mEventTargets.equal_range(eventId);
		for( it = rangeIt.first; it != rangeIt.second; ++it )
		{
			(*it).second->OnEvent( eventId );
		}
	}
	return true;
}

// ------------------------------------------

// version 1
//bool cEventHandler::RegisterTarget(cIEventTarget *pTarget, Uint32 eventId)
//{
//	mEventTargets.push_back( pTarget );
//	return true;
//}

// version 2
bool cEventHandler::RegisterTarget(Uint32 eventId, cIEventTarget *pTarget )
{
	mEventTargets.insert( tEventTargetMap::value_type( eventId, pTarget ) );
	return true;
}

// ------------------------------------------

bool cEventHandler::PostEvent(Uint32 eventId)
{
	mEvents.push( eventId );
	return true;
}

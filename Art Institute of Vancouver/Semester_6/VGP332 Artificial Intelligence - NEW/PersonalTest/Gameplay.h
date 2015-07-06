#ifndef INCLUDED_GAMEPLAY_H
#define INCLUDED_GAMEPLAY_H

//=================================================================================================
// Filename:	Gameplay.h
// Copyright:	Daniel Schenker
// Created:		2012/10/23
// Last Edited:	2012/11/07
// Description:	Gameplay class for game state.
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include <AI.h>
#include "BaseState.h"
#include "Character.h"
#include "ItemBar.h"
#include "Map.h"

// SGE
#include <SGE.h>
using namespace SGE;

// STL
//#include <list>

//=================================================================================================
// Enumerations
//=================================================================================================

namespace Mode
{
	enum eModeType
	{
		kStandard,
		kSearchControl,
		kMapEditor,
		kMax
	};
}

namespace Search
{
	enum eSearchType
	{
		kInvalid = -1,
		kBFS,
		kDFS,
		kDijkstra,
		kMax
	};
}

//=================================================================================================
// Class Declarations
//=================================================================================================

class Gameplay : public BaseState
{
public:
	//Constructor
	Gameplay(GameContext& gc);
	//Destructor
	virtual ~Gameplay();

	// Implements BaseState
	virtual void Load();
	virtual void Unload();
	virtual int Update(float deltaTime);
	virtual void Render();

	void AIInitialize();
	void AITerminate();
	bool AIUpdate();
	void AIUpdateGraph();
	void AISearch(Search::eSearchType searchType);
	void AIRender(const SVector2& offset);

	//Accessors
	const SVector2& GetWaypointStartPos() const			{ return mWaypointStartPos; }
	const SVector2& GetWaypointEndPos() const			{ return mWaypointEndPos; }
	const Mode::eModeType GetCurrentMode() const		{ return mCurrentMode; }
	const SVector2& GetRenderOffset() const				{ return mRenderOffset; }
	const int GetScrollRate() const						{ return mScrollRate; }
	const Search::eSearchType GetSearchType() const		{ return mSearchType; }

	//Mutators
	void SetWaypointStartPos(const SVector2& pos);
	void SetWaypointEndPos(const SVector2& pos);
	void SetCurrentMode(Mode::eModeType mode)			{ mCurrentMode = mode; }
	void SetRenderOffset(const SVector2& offset)		{ mRenderOffset = offset; }
	void SetScrollRate(int scrollrate)					{ mScrollRate = ((scrollrate > 0) ? scrollrate : mDefaultScrollRate); }
	void SetSearchType(Search::eSearchType type)		{ mSearchType = type; }

private:
	//AI
	 //Graph
	Graph mGraph;
	 //Settings
	Search::eSearchType mSearchType;
	 //State
	int mAILastMouseWheelState;
	 // Waypoints
	  // Start
	SVector2 mWaypointStartPos;
	SGE_Sprite mWaypointStartSprite;
	  // End
	SVector2 mWaypointEndPos;
	SGE_Sprite mWaypointEndSprite;

	//Character
	//Character mCharacter;

	// Control
	 //Cursor
	SGE_Cursor mCursor;

	//General
	Mode::eModeType mCurrentMode;
	SVector2 mRenderOffset;
	const int mDefaultScrollRate;
	int mScrollRate;

	// HUD
	ItemBar mItemBar;

	//Map
	 //Data
	Map mMap;
	 //State
	bool mMapModified;

	//World
	World mWorld;
};

#endif // #ifndef INCLUDED_GAMEPLAY_H
#ifndef INCLUDED_BLASTOIDS_NEWGAME_H
#define INCLUDED_BLASTOIDS_NEWGAME_H

//=================================================================================================
// Filename:	NewGame.h
// Copyright:	Daniel Schenker
// Created:		2012/11/09
// Last Edited:	2012/11/27
// Description:	New Game sub-state of the Frontend state.
//				Here is where the settings for a new playthrough are queried.
//					Some of these settings may also be set in the settings sub-state, and as a
//					result save over the same gamecontext file, but not any save files.
//				Inherits from BaseState as a sub-state is just a smaller base state with the same
//					properties.
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "BaseState.h"

// SGE
#include <SGE.h>
using namespace SGE;

//=================================================================================================
// Class Declarations
//=================================================================================================

class NewGame : public BaseState
{
public:
	//Constructor
	NewGame(GameContext& gc);
	//Destructor
	virtual ~NewGame();

	// Implements BaseState
	virtual void Load();
	virtual void Unload();
	virtual int Update(float deltaTime);
	virtual void Render();

private:
	//Title
	SGE_Font mTitleFont;
	SVector2 mTitlePos;

	// Buttons
	 // Ready
	SGE_Button mReadyButton;
	SVector2 mReadyButtonPos;
	 // Back
	SGE_Button mBackButton;
	SVector2 mBackButtonPos;
};

#endif // #ifndef INCLUDED_BLASTOIDS_NEWGAME_H
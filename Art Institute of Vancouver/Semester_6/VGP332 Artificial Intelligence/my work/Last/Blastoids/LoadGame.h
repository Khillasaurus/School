#ifndef INCLUDED_BLASTOIDS_LOADGAME_H
#define INCLUDED_BLASTOIDS_LOADGAME_H

//=================================================================================================
// Filename:	LoadGame.h
// Copyright:	Daniel Schenker
// Created:		2012/11/27
// Last Edited:	2012/11/27
// Description:	Load Game sub-state of the Frontend state.
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

class LoadGame : public BaseState
{
public:
	//Constructor
	LoadGame(GameContext& gc);
	//Destructor
	virtual ~LoadGame();

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

#endif // #ifndef INCLUDED_BLASTOIDS_LOADGAME_H
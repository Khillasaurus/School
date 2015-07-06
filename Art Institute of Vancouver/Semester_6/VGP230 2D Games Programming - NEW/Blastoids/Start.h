#ifndef INCLUDED_BLASTOIDS_START_H
#define INCLUDED_BLASTOIDS_START_H

//=================================================================================================
// Filename:	Start.h
// Copyright:	Daniel Schenker
// Created:		2012/11/09
// Last Edited:	2012/11/27
// Description:	Start sub-state of the Frontend state.
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

class Start : public BaseState
{
public:
	//Constructor
	Start(GameContext& gc);
	//Destructor
	virtual ~Start();

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
	 // New Game
	SGE_Button mNewGameButton;
	SVector2 mNewGameButtonPos;

	 // Load Game
	SGE_Button mLoadGameButton;
	SVector2 mLoadGameButtonPos;

	 // Back
	SGE_Button mBackButton;
	SVector2 mBackButtonPos;
};

#endif // #ifndef INCLUDED_BLASTOIDS_START_H
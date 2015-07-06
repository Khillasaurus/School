#ifndef INCLUDED_BLASTOIDS_GAMEPLAY_H
#define INCLUDED_BLASTOIDS_GAMEPLAY_H

//=================================================================================================
// Filename:	Gameplay.h
// Copyright:	Daniel Schenker
// Created:		2012/11/27
// Last Edited:	2012/11/27
// Description:	Gameplay sub-state of the Frontend state.
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

private:
	//Title
	SGE_Font mTitleFont;
	SVector2 mTitlePos;

	// Buttons
	 // Keybindings
	SGE_Button mKeybindingsButton;
	SVector2 mKeybindingsButtonPos;

	 // Back
	SGE_Button mBackButton;
	SVector2 mBackButtonPos;
};

#endif // #ifndef INCLUDED_BLASTOIDS_GAMEPLAY_H
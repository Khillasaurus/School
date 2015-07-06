#ifndef INCLUDED_BLASTOIDS_KEYBINDINGS_H
#define INCLUDED_BLASTOIDS_KEYBINDINGS_H

//=================================================================================================
// Filename:	Keybindings.h
// Copyright:	Daniel Schenker
// Created:		2012/11/27
// Last Edited:	2012/11/27
// Description:	Keybindings sub-state of the Frontend state.
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

class Keybindings : public BaseState
{
public:
	//Constructor
	Keybindings(GameContext& gc);
	//Destructor
	virtual ~Keybindings();

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
	 // Back
	SGE_Button mBackButton;
	SVector2 mBackButtonPos;
};

#endif // #ifndef INCLUDED_BLASTOIDS_KEYBINDINGS_H
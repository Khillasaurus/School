#ifndef INCLUDED_FRONTEND_H
#define INCLUDED_FRONTEND_H

//=================================================================================================
// Filename:	Frontend.h
// Copyright:	Daniel Schenker
// Created:		2012/10/23
// Last Edited:	2012/10/30
// Description:	Frontend class for game state.
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

// SGE
#include <SGE.h>
using namespace SGE;

//Daniel Schenker
#include "BaseState.h"

//=================================================================================================
// Class Declarations
//=================================================================================================

class Frontend : public BaseState
{
public:
	//Constructor
	Frontend(GameContext& gc);
	//Destructor
	virtual ~Frontend();

	// Implements BaseState
	virtual void Load();
	virtual void Unload();
	virtual int Update(float deltaTime);
	virtual void Render();

private:
	SGE_Cursor mCursor;
	SGE_Font mFont;
	SGE_Button mStartButton;
	SGE_Button mLevel1Button;
	SGE_Button mLevel2Button;
	SGE_Button mQuitButton;
};

#endif // #ifndef INCLUDED_FRONTEND_H
#ifndef INCLUDED_FRONTEND_H
#define INCLUDED_FRONTEND_H

//=================================================================================================
// Filename:	Frontend.h
// Copyright:	Daniel Schenker
// Created:		2012/10/23
// Last Edited:	2012/11/04
// Description:	Frontend class for game state.
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
	SGE_Font mTitleFont;
	SGE_Button mStartButton;
	//SGE_Button mLevel1Button;
	//SGE_Button mLevel2Button;
	//SGE_Button mLevel3Button;
	SGE_Button mSaveButton;
	SGE_Button mLoadButton;
	SGE_Button mQuitButton;
};

#endif // #ifndef INCLUDED_FRONTEND_H
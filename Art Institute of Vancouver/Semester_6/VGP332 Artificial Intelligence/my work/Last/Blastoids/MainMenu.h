#ifndef INCLUDED_BLASTOIDS_MAINMENU_H
#define INCLUDED_BLASTOIDS_MAINMENU_H

//=================================================================================================
// Filename:	MainMenu.h
// Copyright:	Daniel Schenker
// Created:		2012/11/09
// Last Edited:	2012/11/27
// Description:	Main Menu sub-state of the Frontend state.
//				First interactable screen shown in the game.
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

class MainMenu : public BaseState
{
public:
	//Constructor
	MainMenu(GameContext& gc);
	//Destructor
	virtual ~MainMenu();

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
	SVector2 mButtonDefaultPos;
	float mButtonVerticalSpacing;
	SGE_Button mStartButton;
	SGE_Button mSettingsButton;
	//SGE_Button mStatisticsButton;
	SGE_Button mQuitButton;
};

#endif // #ifndef INCLUDED_BLASTOIDS_MAINMENU_H
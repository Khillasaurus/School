#ifndef INCLUDED_BLASTOIDS_SETTINGS_H
#define INCLUDED_BLASTOIDS_SETTINGS_H

//=================================================================================================
// Filename:	Settings.h
// Copyright:	Daniel Schenker
// Created:		2012/11/09
// Last Edited:	2012/11/27
// Description:	Settings sub-state of the Frontend state.
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

class Settings : public BaseState
{
public:
	//Constructor
	Settings(GameContext& gc);
	//Destructor
	virtual ~Settings();

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
	 // Gameplay
	SGE_Button mGameplayButton;
	SVector2 mGameplayButtonPos;

	 // Audio
	SGE_Button mAudioButton;
	SVector2 mAudioButtonPos;

	// Video
	SGE_Button mVideoButton;
	SVector2 mVideoButtonPos;

	 // Back
	SGE_Button mBackButton;
	SVector2 mBackButtonPos;
};

#endif // #ifndef INCLUDED_BLASTOIDS_SETTINGS_H
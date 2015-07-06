//=================================================================================================
// Filename:	Audio.cpp
// Copyright:	Daniel Schenker
// Created:		2012/11/27
// Last Edited:	2012/11/27
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "Audio.h"
#include "ReturnCodes.h"

//=================================================================================================
// Class Defintions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructors
//-------------------------------------------------------------------------------------------------

Audio::Audio(GameContext& gc)
: BaseState(gc)
, mTitlePos(kScreenWidth * 0.3125f, kScreenHeight * 0.14f)
, mBackButtonPos(kScreenWidth * 0.85f, kScreenHeight * 0.9f)
{
}

//-------------------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------------------

Audio::~Audio()
{
}


//-------------------------------------------------------------------------------------------------
// Implements BaseState
//-------------------------------------------------------------------------------------------------

void Audio::Load()
{
	//Title
	mTitleFont.Load(72);
	mTitleFont.SetColor(30, 180, 200);

	// Buttons
	 // Back
	mBackButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mBackButton.SetPosition(mBackButtonPos);
	mBackButton.SetText("Back", 255, 255, 255);
}

//-------------------------------------------------------------------------------------------------

void Audio::Unload()
{
	//Title
	mTitleFont.Unload();

	// Buttons
	mBackButton.Unload();
}

//-------------------------------------------------------------------------------------------------


int Audio::Update(float deltaTime)
{
	// Buttons
	mBackButton.Update(deltaTime);

	if(mBackButton.IsPressed())
	{
		return SubState::kSettings;
	}
	return SubState::kAudio;
}

//-------------------------------------------------------------------------------------------------

void Audio::Render()
{
	//Title
	mTitleFont.Print("AUDIO", static_cast<int>(mTitlePos.x), static_cast<int>(mTitlePos.y));

	// Buttons
	mBackButton.Render();
}
//=================================================================================================
// Filename:	Settings.cpp
// Copyright:	Daniel Schenker
// Created:		2012/11/09
// Last Edited:	2012/11/09
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "Settings.h"
#include "ReturnCodes.h"

//=================================================================================================
// Class Defintions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructors
//-------------------------------------------------------------------------------------------------

Settings::Settings(GameContext& gc)
: BaseState(gc)
, mTitlePos(kScreenWidth * 0.3125f, kScreenHeight * 0.14f)
//, mGameplayButtonPos(kScreenWidth * 0.08f, kScreenHeight * 0.55f)
//, mAudioButtonPos(mGameplayButtonPos.x, mGameplayButtonPos.y + 50.0f)
//, mVideoButtonPos(mGameplayButtonPos.x, mGameplayButtonPos.y + 100.0f)
, mBackButtonPos(kScreenWidth * 0.85f, kScreenHeight * 0.9f)
{
}

//-------------------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------------------

Settings::~Settings()
{
}


//-------------------------------------------------------------------------------------------------
// Implements BaseState
//-------------------------------------------------------------------------------------------------

void Settings::Load()
{
	//Title
	mTitleFont.Load(72);
	mTitleFont.SetColor(30, 180, 200);

	// Buttons
	/*
	 // Gameplay
	mGameplayButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mGameplayButton.SetPosition(mGameplayButtonPos);
	mGameplayButton.SetText("Gameplay", 255, 255, 255);

	 // Audio
	mAudioButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mAudioButton.SetPosition(mAudioButtonPos);
	mAudioButton.SetText("Audio", 255, 255, 255);

	 // Video
	mVideoButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mVideoButton.SetPosition(mVideoButtonPos);
	mVideoButton.SetText("Video", 255, 255, 255);
	*/

	// Images
	mInstructions.Load("Instructions.png");
	int width = mInstructions.GetWidth();
	int height = mInstructions.GetHeight();
	mInstructions.SetPosition((kScreenWidth - width) * 0.5, (kScreenHeight - height) * 0.5);

	 // Back
	mBackButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mBackButton.SetPosition(mBackButtonPos);
	mBackButton.SetText("Back", 255, 255, 255);
}

//-------------------------------------------------------------------------------------------------

void Settings::Unload()
{
	//Title
	mTitleFont.Unload();

	// Images
	mInstructions.Unload();

	// Buttons
	/*
	mGameplayButton.Unload();
	mAudioButton.Unload();
	mVideoButton.Unload();
	*/
	mBackButton.Unload();
}

//-------------------------------------------------------------------------------------------------


int Settings::Update(float deltaTime)
{
	// Buttons
	/*
	mGameplayButton.Update(deltaTime);
	mAudioButton.Update(deltaTime);
	mVideoButton.Update(deltaTime);
	*/
	mBackButton.Update(deltaTime);

	/*
	if(mGameplayButton.IsPressed())
	{
		return SubState::kGameplay;
	}
	else if(mAudioButton.IsPressed())
	{
		return SubState::kAudio;
	}
	else if(mVideoButton.IsPressed())
	{
		return SubState::kVideo;
	}
	*/
	/*else */if(mBackButton.IsPressed())
	{
		return SubState::kMainMenu;
	}
	return SubState::kSettings;
}

//-------------------------------------------------------------------------------------------------

void Settings::Render()
{
	//Title
	//mTitleFont.Print("SETTINGS", static_cast<int>(mTitlePos.x), static_cast<int>(mTitlePos.y));
	mTitleFont.Print("INSTRUCTIONS", static_cast<int>(mTitlePos.x), static_cast<int>(mTitlePos.y));

	// Images
	mInstructions.Render();

	// Buttons
	/*
	mGameplayButton.Render();
	mAudioButton.Render();
	mVideoButton.Render();
	*/
	mBackButton.Render();
}
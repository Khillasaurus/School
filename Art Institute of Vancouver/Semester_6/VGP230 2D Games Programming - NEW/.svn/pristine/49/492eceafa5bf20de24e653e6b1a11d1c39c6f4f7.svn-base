//=================================================================================================
// Filename:	Video.cpp
// Copyright:	Daniel Schenker
// Created:		2012/11/27
// Last Edited:	2012/11/27
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "Video.h"
#include "ReturnCodes.h"

//=================================================================================================
// Class Defintions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructors
//-------------------------------------------------------------------------------------------------

Video::Video(GameContext& gc)
: BaseState(gc)
, mTitlePos(kScreenWidth * 0.3125f, kScreenHeight * 0.14f)
, mBackButtonPos(kScreenWidth * 0.85f, kScreenHeight * 0.9f)
{
}

//-------------------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------------------

Video::~Video()
{
}


//-------------------------------------------------------------------------------------------------
// Implements BaseState
//-------------------------------------------------------------------------------------------------

void Video::Load()
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

void Video::Unload()
{
	//Title
	mTitleFont.Unload();

	// Buttons
	mBackButton.Unload();
}

//-------------------------------------------------------------------------------------------------


int Video::Update(float deltaTime)
{
	// Buttons
	mBackButton.Update(deltaTime);

	if(mBackButton.IsPressed())
	{
		return SubState::kSettings;
	}
	return SubState::kVideo;
}

//-------------------------------------------------------------------------------------------------

void Video::Render()
{
	//Title
	mTitleFont.Print("VIDEO", static_cast<int>(mTitlePos.x), static_cast<int>(mTitlePos.y));

	// Buttons
	mBackButton.Render();
}
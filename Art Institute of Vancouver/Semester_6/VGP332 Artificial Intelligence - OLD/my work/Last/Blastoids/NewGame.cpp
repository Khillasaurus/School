//=================================================================================================
// Filename:	NewGame.cpp
// Copyright:	Daniel Schenker
// Created:		2012/11/09
// Last Edited:	2012/11/09
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "NewGame.h"
#include "ReturnCodes.h"

//=================================================================================================
// Class Defintions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructors
//-------------------------------------------------------------------------------------------------

NewGame::NewGame(GameContext& gc)
: BaseState(gc)
, mTitlePos(kScreenWidth * 0.3125f, kScreenHeight * 0.14f)
, mReadyButtonPos(kScreenWidth * 0.08f, kScreenHeight * 0.55f)
, mBackButtonPos(kScreenWidth * 0.85f, kScreenHeight * 0.9f)
{
}

//-------------------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------------------

NewGame::~NewGame()
{
}


//-------------------------------------------------------------------------------------------------
// Implements BaseState
//-------------------------------------------------------------------------------------------------

void NewGame::Load()
{
	//Title
	mTitleFont.Load(72);
	mTitleFont.SetColor(30, 180, 200);

	// Buttons
	 // Ready
	mReadyButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mReadyButton.SetPosition(mReadyButtonPos);
	mReadyButton.SetText("Ready!", 255, 255, 255);
	 // Back
	mBackButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mBackButton.SetPosition(mBackButtonPos);
	mBackButton.SetText("Back", 255, 255, 255);
}

//-------------------------------------------------------------------------------------------------

void NewGame::Unload()
{
	//Title
	mTitleFont.Unload();

	// Buttons
	mReadyButton.Unload();
	mBackButton.Unload();
}

//-------------------------------------------------------------------------------------------------


int NewGame::Update(float deltaTime)
{
	// Buttons
	mReadyButton.Update(deltaTime);
	mBackButton.Update(deltaTime);

	if(mReadyButton.IsPressed())
	{
		return SubState::kGame;
	}
	else if(mBackButton.IsPressed())
	{
		return SubState::kStart;
	}
	return SubState::kNewGame;
}

//-------------------------------------------------------------------------------------------------

void NewGame::Render()
{
	//Title
	mTitleFont.Print("NEW GAME", static_cast<int>(mTitlePos.x), static_cast<int>(mTitlePos.y));

	// Buttons
	mReadyButton.Render();
	mBackButton.Render();
}
//=================================================================================================
// Filename:	Gameplay.cpp
// Copyright:	Daniel Schenker
// Created:		2012/11/27
// Last Edited:	2012/11/27
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "Gameplay.h"
#include "ReturnCodes.h"

//=================================================================================================
// Class Defintions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructors
//-------------------------------------------------------------------------------------------------

Gameplay::Gameplay(GameContext& gc)
: BaseState(gc)
, mTitlePos(kScreenWidth * 0.3125f, kScreenHeight * 0.14f)
, mKeybindingsButtonPos(kScreenWidth * 0.08f, kScreenHeight * 0.55f)
, mBackButtonPos(kScreenWidth * 0.85f, kScreenHeight * 0.9f)
{
}

//-------------------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------------------

Gameplay::~Gameplay()
{
}


//-------------------------------------------------------------------------------------------------
// Implements BaseState
//-------------------------------------------------------------------------------------------------

void Gameplay::Load()
{
	//Title
	mTitleFont.Load(72);
	mTitleFont.SetColor(30, 180, 200);

	// Buttons
	 // Keybindings
	mKeybindingsButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mKeybindingsButton.SetPosition(mKeybindingsButtonPos);
	mKeybindingsButton.SetText("Keybindings", 255, 255, 255);

	 // Back
	mBackButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mBackButton.SetPosition(mBackButtonPos);
	mBackButton.SetText("Back", 255, 255, 255);
}

//-------------------------------------------------------------------------------------------------

void Gameplay::Unload()
{
	//Title
	mTitleFont.Unload();

	// Buttons
	mKeybindingsButton.Unload();
	mBackButton.Unload();
}

//-------------------------------------------------------------------------------------------------


int Gameplay::Update(float deltaTime)
{
	// Buttons
	mKeybindingsButton.Update(deltaTime);
	mBackButton.Update(deltaTime);

	if(mKeybindingsButton.IsPressed())
	{
		return SubState::kKeybindings;
	}
	else if(mBackButton.IsPressed())
	{
		return SubState::kSettings;
	}
	return SubState::kGameplay;
}

//-------------------------------------------------------------------------------------------------

void Gameplay::Render()
{
	//Title
	mTitleFont.Print("GAMEPLAY", static_cast<int>(mTitlePos.x), static_cast<int>(mTitlePos.y));

	// Buttons
	mKeybindingsButton.Render();
	mBackButton.Render();
}
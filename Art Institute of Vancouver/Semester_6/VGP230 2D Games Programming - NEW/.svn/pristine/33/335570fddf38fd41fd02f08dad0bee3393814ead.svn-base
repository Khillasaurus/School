//=================================================================================================
// Filename:	Frontend.cpp
// Copyright:	Daniel Schenker
// Created:		2012/10/23
// Last Edited:	2012/10/30
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

// Daniel Schenker
#include "Frontend.h"
#include "GameStates.h"

//=================================================================================================
// Class Definitions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------------------------------

Frontend::Frontend(GameContext& gc)
: BaseState(gc)
{
}

//-------------------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------------------

Frontend::~Frontend()
{
}

//-------------------------------------------------------------------------------------------------
// Implements BaseState
//-------------------------------------------------------------------------------------------------

void Frontend::Load()
{
	mCursor.Load("sword.png");
	mFont.Load(72);

	mStartButton.Load("button_on.png", "button_off.png");
	mStartButton.SetPosition(100.0f, 400.0f);
	mStartButton.SetText("START", 255, 255, 255);

	mLevel1Button.Load("button_on.png", "button_off.png");
	mLevel1Button.SetPosition(100.0f, 450.0f);
	mLevel1Button.SetText("Level 1", 255, 255, 255);

	mLevel2Button.Load("button_on.png", "button_off.png");
	mLevel2Button.SetPosition(100.0f, 500.0f);
	mLevel2Button.SetText("Level 2", 255, 255, 255);

	mQuitButton.Load("button_on.png", "button_off.png");
	mQuitButton.SetPosition(100.0f, 550.0f);
	mQuitButton.SetText("QUIT", 255, 255, 255);
}

//-------------------------------------------------------------------------------------------------

void Frontend::Unload()
{
	mCursor.Unload();
	mFont.Unload();
	mStartButton.Unload();
	mLevel1Button.Unload();
	mLevel2Button.Unload();
	mQuitButton.Unload();
}

//-------------------------------------------------------------------------------------------------

int Frontend::Update(float deltaTime)
{
	mCursor.Update(deltaTime);
	mStartButton.Update(deltaTime);
	mLevel1Button.Update(deltaTime);
	mLevel2Button.Update(deltaTime);
	mQuitButton.Update(deltaTime);

	// Check if we need to change state
	GameState::Type nextState = GameState::Invalid;
	if(mStartButton.IsPressed())
	{
		nextState = GameState::Gameplay;
	}
	else if(mLevel1Button.IsPressed())
	{
		mGameContext.SetLevel(0);
	}
	else if(mLevel2Button.IsPressed())
	{
		mGameContext.SetLevel(1);
	}
	else if(mQuitButton.IsPressed())
	{
		nextState = GameState::Quit;
	}
	return nextState;
}

//-------------------------------------------------------------------------------------------------

void Frontend::Render()
{
	mFont.Print("ZELDA GAME", 200, 200);
	mStartButton.Render();
	mLevel1Button.Render();
	mLevel2Button.Render();
	mQuitButton.Render();
	mCursor.Render();
}

//-------------------------------------------------------------------------------------------------
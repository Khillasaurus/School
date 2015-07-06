//=================================================================================================
// Filename:	Frontend.cpp
// Copyright:	Daniel Schenker
// Created:		2012/10/23
// Last Edited:	2012/10/23
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

// Daniel Schenker
#include "Frontend.h"
#include "GameStates.h"

//=================================================================================================
// Class Declarations
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------------------------------

Frontend::Frontend()
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
	mStartButton.SetPosition(100.0f, 300.0f);
	mStartButton.SetText("START", 255, 255, 255);

	mQuitButton.Load("button_on.png", "button_off.png");
	mQuitButton.SetPosition(100.0f, 400.0f);
	mQuitButton.SetText("QUIT", 255, 255, 255);
}

//-------------------------------------------------------------------------------------------------

void Frontend::Unload()
{
	mCursor.Unload();
	mFont.Unload();
	mStartButton.Unload();
	mQuitButton.Unload();
}

//-------------------------------------------------------------------------------------------------

int Frontend::Update(float deltaTime)
{
	mCursor.Update(deltaTime);
	mStartButton.Update(deltaTime);
	mQuitButton.Update(deltaTime);

	// Check if we need to change state
	GameState::Type nextState = GameState::Invalid;
	if(mStartButton.IsPressed())
	{
		nextState = GameState::Gameplay;
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
	mQuitButton.Render();
	mCursor.Render();
}

//-------------------------------------------------------------------------------------------------
//=================================================================================================
// Filename:	Frontend.cpp
// Copyright:	Daniel Schenker
// Created:		2012/10/23
// Last Edited:	2012/11/04
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
	//Cursor
	mCursor.Load("PeterChan/sword.png");

	//Title
	mTitleFont.Load(72);
	mTitleFont.SetColor(30, 180, 200);

	// Buttons
	const SVector2 defaultOffset(100.0f, 300.0f);
	const float verticalSpacing = 50.0f;
	mStartButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mStartButton.SetPosition(defaultOffset);
	mStartButton.SetText("START", 255, 255, 255);

	/*
	mLevel1Button.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mLevel1Button.SetPosition(defaultOffset.x, defaultOffset.y + verticalSpacing);
	mLevel1Button.SetText("Level 1", 255, 255, 255);

	mLevel2Button.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mLevel2Button.SetPosition(defaultOffset.x, defaultOffset.y + (verticalSpacing * 2));
	mLevel2Button.SetText("Level 2", 255, 255, 255);

	mLevel3Button.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mLevel3Button.SetPosition(defaultOffset.x, defaultOffset.y + (verticalSpacing * 3));
	mLevel3Button.SetText("Level 3", 255, 255, 255);
	*/

	mSaveButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mSaveButton.SetPosition(defaultOffset.x, defaultOffset.y + (verticalSpacing * 4));
	mSaveButton.SetText("Save", 255, 255, 255);

	mLoadButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mLoadButton.SetPosition(defaultOffset.x, defaultOffset.y + (verticalSpacing * 5));
	mLoadButton.SetText("Load", 255, 255, 255);

	mQuitButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mQuitButton.SetPosition(defaultOffset.x, defaultOffset.y + (verticalSpacing * 6));
	mQuitButton.SetText("QUIT", 255, 255, 255);
}

//-------------------------------------------------------------------------------------------------

void Frontend::Unload()
{
	mCursor.Unload();
	mTitleFont.Unload();
	mStartButton.Unload();
	/*
	mLevel1Button.Unload();
	mLevel2Button.Unload();
	mLevel3Button.Unload();
	*/
	mSaveButton.Unload();
	mLoadButton.Unload();
	mQuitButton.Unload();
}

//-------------------------------------------------------------------------------------------------

int Frontend::Update(float deltaTime)
{
	mCursor.Update(deltaTime);
	mStartButton.Update(deltaTime);
	/*
	mLevel1Button.Update(deltaTime);
	mLevel2Button.Update(deltaTime);
	mLevel3Button.Update(deltaTime);
	*/
	mSaveButton.Update(deltaTime);
	mLoadButton.Update(deltaTime);
	mQuitButton.Update(deltaTime);

	// Check if we need to change state
	GameState::Type nextState = GameState::Invalid;
	if(mStartButton.IsPressed())
	{
		nextState = GameState::Gameplay;
	}
	/*
	else if(mLevel1Button.IsPressed())
	{
		mGameContext.SetLevel(0);
	}
	else if(mLevel2Button.IsPressed())
	{
		mGameContext.SetLevel(1);
	}
	else if(mLevel3Button.IsPressed())
	{
		mGameContext.SetLevel(2);
	}
	*/
	else if(mSaveButton.IsPressed())
	{
		mGameContext.SaveData("GameContext_SaveData.txt");
	}
	else if(mLoadButton.IsPressed())
	{
		mGameContext.LoadData("GameContext_SaveData.txt");
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
	mTitleFont.Print("PersonalTest.vcproj - Testing Pathfinding", 100, 100);
	mStartButton.Render();
	/*
	mLevel1Button.Render();
	mLevel2Button.Render();
	mLevel3Button.Render();
	*/
	mSaveButton.Render();
	mLoadButton.Render();
	mQuitButton.Render();
	mCursor.Render();
}
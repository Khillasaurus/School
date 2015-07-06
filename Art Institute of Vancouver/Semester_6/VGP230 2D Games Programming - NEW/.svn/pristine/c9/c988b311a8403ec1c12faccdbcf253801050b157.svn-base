//=================================================================================================
// Filename:	MainMenu.cpp
// Copyright:	Daniel Schenker
// Created:		2012/11/09
// Last Edited:	2012/11/09
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "MainMenu.h"
#include "ReturnCodes.h"

//=================================================================================================
// Class Defintions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructors
//-------------------------------------------------------------------------------------------------

MainMenu::MainMenu(GameContext& gc)
: BaseState(gc)
, mTitlePos(kScreenWidth * 0.3125f, kScreenHeight * 0.14f)
, mButtonDefaultPos(kScreenWidth * 0.08f, kScreenHeight * 0.55f)
, mButtonVerticalSpacing(50.0f)
{
}

//-------------------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------------------

MainMenu::~MainMenu()
{
}

//-------------------------------------------------------------------------------------------------
// Implements BaseState
//-------------------------------------------------------------------------------------------------

void MainMenu::Load()
{
	//Title
	mTitleFont.Load(72);
	mTitleFont.SetColor(30, 180, 200);

	// Buttons
	 // Start
	mStartButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mStartButton.SetPosition(mButtonDefaultPos);
	mStartButton.SetText("Start", 255, 255, 255);

	 // Settings
	mSettingsButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mSettingsButton.SetPosition(mButtonDefaultPos.x, mButtonDefaultPos.y + mButtonVerticalSpacing);
	mSettingsButton.SetText("Settings", 255, 255, 255);

	 // Statistics
	mStatisticsButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mStatisticsButton.SetPosition(mButtonDefaultPos.x, mButtonDefaultPos.y + (mButtonVerticalSpacing * 2));
	mStatisticsButton.SetText("Statistics", 255, 255, 255);

	 // Quit
	mQuitButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mQuitButton.SetPosition(mButtonDefaultPos.x, kScreenHeight * 0.9f);
	mQuitButton.SetText("Quit", 255, 255, 255);
}

//-------------------------------------------------------------------------------------------------

void MainMenu::Unload()
{
	//Title
	mTitleFont.Unload();

	// Buttons
	mStartButton.Unload();
	mSettingsButton.Unload();
	mStatisticsButton.Unload();
	mQuitButton.Unload();
}

//-------------------------------------------------------------------------------------------------

int MainMenu::Update(float deltaTime)
{
	// Buttons
	mStartButton.Update(deltaTime);
	mSettingsButton.Update(deltaTime);
	mStatisticsButton.Update(deltaTime);
	mQuitButton.Update(deltaTime);

	if(mStartButton.IsPressed())
	{
		return SubState::kStart;
	}
	else if(mSettingsButton.IsPressed())
	{
		return SubState::kSettings;
	}
	else if(mStatisticsButton.IsPressed())
	{
		return SubState::kStatistics;
	}
	else if(mQuitButton.IsPressed())
	{
		return SubState::kQuit;
	}
	return SubState::kMainMenu;
}

//-------------------------------------------------------------------------------------------------

void MainMenu::Render()
{
	//Title
	mTitleFont.Print("BLASTOIDS", static_cast<int>(mTitlePos.x), static_cast<int>(mTitlePos.y));

	// Buttons
	mStartButton.Render();
	mSettingsButton.Render();
	mStatisticsButton.Render();
	mQuitButton.Render();
}
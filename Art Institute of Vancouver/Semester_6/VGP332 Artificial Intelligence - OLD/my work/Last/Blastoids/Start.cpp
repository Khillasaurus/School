//=================================================================================================
// Filename:	Start.cpp
// Copyright:	Daniel Schenker
// Created:		2012/11/09
// Last Edited:	2012/11/09
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "Start.h"
#include "ReturnCodes.h"

//=================================================================================================
// Class Defintions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructors
//-------------------------------------------------------------------------------------------------

Start::Start(GameContext& gc)
: BaseState(gc)
, mTitlePos(kScreenWidth * 0.3125f, kScreenHeight * 0.14f)
, mNewGameButtonPos(kScreenWidth * 0.08f, kScreenHeight * 0.55f)
, mLoadGameButtonPos(mNewGameButtonPos.x, mNewGameButtonPos.y + 50.0f)
, mBackButtonPos(kScreenWidth * 0.85f, kScreenHeight * 0.9f)
{
}

//-------------------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------------------

Start::~Start()
{
}


//-------------------------------------------------------------------------------------------------
// Implements BaseState
//-------------------------------------------------------------------------------------------------

void Start::Load()
{
	//Title
	mTitleFont.Load(72);
	mTitleFont.SetColor(30, 180, 200);

	// Buttons
	 // New Game
	mNewGameButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mNewGameButton.SetPosition(mNewGameButtonPos);
	mNewGameButton.SetText("New Game", 255, 255, 255);

	 // Load Game
	mLoadGameButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mLoadGameButton.SetPosition(mLoadGameButtonPos);
	mLoadGameButton.SetText("Load Game", 255, 255, 255);

	 // Back
	mBackButton.Load("PeterChan/button_on.png", "PeterChan/button_off.png");
	mBackButton.SetPosition(mBackButtonPos);
	mBackButton.SetText("Back", 255, 255, 255);
}

//-------------------------------------------------------------------------------------------------

void Start::Unload()
{
	//Title
	mTitleFont.Unload();

	// Buttons
	mNewGameButton.Unload();
	mLoadGameButton.Unload();
	mBackButton.Unload();
}

//-------------------------------------------------------------------------------------------------


int Start::Update(float deltaTime)
{
	// Buttons
	mNewGameButton.Update(deltaTime);
	mLoadGameButton.Update(deltaTime);
	mBackButton.Update(deltaTime);

	if(mNewGameButton.IsPressed())
	{
		return SubState::kNewGame;
	}
	else if(mLoadGameButton.IsPressed())
	{
		return SubState::kLoadGame;
	}
	else if(mBackButton.IsPressed())
	{
		return SubState::kMainMenu;
	}
	return SubState::kStart;
}

//-------------------------------------------------------------------------------------------------

void Start::Render()
{
	//Title
	mTitleFont.Print("START", static_cast<int>(mTitlePos.x), static_cast<int>(mTitlePos.y));

	// Buttons
	mNewGameButton.Render();
	mLoadGameButton.Render();
	mBackButton.Render();
}
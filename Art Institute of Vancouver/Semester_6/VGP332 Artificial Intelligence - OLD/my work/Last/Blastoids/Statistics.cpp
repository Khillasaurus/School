//=================================================================================================
// Filename:	Statistics.cpp
// Copyright:	Daniel Schenker
// Created:		2012/11/09
// Last Edited:	2012/11/09
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "Statistics.h"
#include "ReturnCodes.h"

//=================================================================================================
// Class Defintions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructors
//-------------------------------------------------------------------------------------------------

Statistics::Statistics(GameContext& gc)
: BaseState(gc)
, mTitlePos(kScreenWidth * 0.3125f, kScreenHeight * 0.14f)
, mBackButtonPos(kScreenWidth * 0.85f, kScreenHeight * 0.9f)
{
}

//-------------------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------------------

Statistics::~Statistics()
{
}


//-------------------------------------------------------------------------------------------------
// Implements BaseState
//-------------------------------------------------------------------------------------------------

void Statistics::Load()
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

void Statistics::Unload()
{
	//Title
	mTitleFont.Unload();

	// Buttons
	mBackButton.Unload();
}

//-------------------------------------------------------------------------------------------------


int Statistics::Update(float deltaTime)
{
	// Buttons
	mBackButton.Update(deltaTime);

	if(mBackButton.IsPressed())
	{
		return SubState::kMainMenu;
	}
	return SubState::kStatistics;
}

//-------------------------------------------------------------------------------------------------

void Statistics::Render()
{
	//Title
	mTitleFont.Print("STATISTICS", static_cast<int>(mTitlePos.x), static_cast<int>(mTitlePos.y));

	// Buttons
	mBackButton.Render();
}
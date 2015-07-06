//=================================================================================================
// File:		Room.cpp
// Created:		2012/09/05
// Last Edited:	2012/10/12
// Copyright:	Daniel Schenker
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

// SGE
#include "graphics/CSprite.h"
#include "graphics/CTexture.h"

//Daniel Schenker
#include "Room.h"
#include "States.h"

//=================================================================================================
// Class Definitions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constuctors
//-------------------------------------------------------------------------------------------------

Room::Room(const char* bgTexture)
{
	//Load Resources
	 //Graphics
	  //Background
	mBgTexture.Load(bgTexture);
	mBgSprite.AddTexture(&mBgTexture);
	mBgSprite.SetDepth(StateDepth::Background);

	//Initialize Positions
	 //Backgrounds
	//Commented out because GetDimensionX() does not exist in SGE\Graphics\CSprite
	//if(mBgSprite.GetDimensionX() <= StateScreen::kWinWidth)
	int bgX;
	int bgY;
	mBgSprite.GetDimension(bgX, bgY);
	if(bgX <= StateScreen::kWinWidth)
	{
		mBgSprite.SetPosition(0.0f, 0.0f);
	}
	else
	{
		//Commented out because GetDimensionX()  and GetDimensionY do not exist in SGE\Graphics\CSprite
		//mBgSprite.SetPosition(-(mBgSprite.GetDimensionX() - StateScreen::kWinWidth), -(mBgSprite.GetDimensionY() -StateScreen::kWinHeight));
		mBgSprite.SetPosition(-(static_cast<float>(bgX) - StateScreen::kWinWidth), -(static_cast<float>(bgY) -StateScreen::kWinHeight));
	}
}

//-------------------------------------------------------------------------------------------------
// Deconstructor
//-------------------------------------------------------------------------------------------------

Room::~Room()
{
}

//-------------------------------------------------------------------------------------------------
// SGE Specific
//-------------------------------------------------------------------------------------------------

void Room::Render()
{
	//Background
	mBgSprite.Render();
}
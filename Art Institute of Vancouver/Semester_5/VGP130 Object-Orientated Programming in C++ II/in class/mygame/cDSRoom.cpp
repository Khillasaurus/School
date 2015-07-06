//====================================================================================================
//File:			cDSRoom.cpp
//Created:		2012/09/05
//Copyright:	Daniel Schenker
//====================================================================================================

//====================================================================================================
//Includes
//====================================================================================================

//Precompiled headers
#include "stdafx.h"

//SGE
#include "graphics/CSprite.h"
#include "graphics/CTexture.h"

//Daniel Schenker
#include "cDSRoom.h"
#include "cDSApp.h"

//====================================================================================================
//Class Definitions
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//Constuctors
//----------------------------------------------------------------------------------------------------

cDSRoom::cDSRoom(const char* bgTexture)
{
	//Load Resources
	 //Graphics
	  //Background
	mBgTexture.Load(bgTexture);
	mBgSprite.AddTexture(&mBgTexture);
	mBgSprite.SetDepth(cDSApp::msDepthBackground);

	//Initialize Positions
	 //Backgrounds
	if(mBgSprite.GetDimensionX() <= cDSApp::msScreenWidth)
	{
		mBgSprite.SetPosition(0, 0);
	}
	else
	{
		mBgSprite.SetPosition(-(mBgSprite.GetDimensionX() - cDSApp::msScreenWidth), -(mBgSprite.GetDimensionY() -cDSApp::msScreenHeight));
	}
}

//----------------------------------------------------------------------------------------------------
//Deconstructor
//----------------------------------------------------------------------------------------------------

cDSRoom::~cDSRoom()
{
}

//----------------------------------------------------------------------------------------------------
//General Member Functions
//----------------------------------------------------------------------------------------------------

void cDSRoom::Render()
{
	//Background
	mBgSprite.Render();
}
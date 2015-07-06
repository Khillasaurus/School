//====================================================================================================
//File:			cDSRoomMainMenu.cpp
//Created:		2012/09/05
//Copyright:	Daniel Schenker
//====================================================================================================

//====================================================================================================
//Includes
//====================================================================================================

//Precompiled headers
#include "stdafx.h"

//SGE
#include "Input/Input.h"

//Daniel Schenker
#include "cDSRoomMainMenu.h"
#include "cDSApp.h"

//====================================================================================================
//Class Definitions
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//Constuctors
//----------------------------------------------------------------------------------------------------

cDSRoomMainMenu::cDSRoomMainMenu(const char* bgTexture) : cDSRoom(bgTexture)
{
	//Create Objects
	 //Buttons
	mpButtonStart = new cDSMenuButton((cDSApp::msScreenWidth / 2) - (168 / 2), (cDSApp::msScreenHeight / 3) - (64 / 2), 168, 64, "./Resources/Textures/Buttons/start_up.png", "./Resources/Textures/Buttons/start_hover.png", "./Resources/Textures/Buttons/start_down.png", "./Resources/Textures/Buttons/start_click.png", false, cDSApp::msDepthButton);
	mpButtonOptions = new cDSMenuButton((cDSApp::msScreenWidth / 2) - (168 / 2), (cDSApp::msScreenHeight / 3) + (64 / 2) + 4, 168, 64, "./Resources/Textures/Buttons/options_up.png", "./Resources/Textures/Buttons/options_hover.png", "./Resources/Textures/Buttons/options_down.png", "./Resources/Textures/Buttons/options_click.png", false, cDSApp::msDepthButton);

	//Load Resources
	 //Graphics
	  //Title
	mTitleTexture.Load("./Resources/Textures/Graphics/title_v1.png");
	mTitleSprite.AddTexture(&mTitleTexture);
	mTitleSprite.SetDepth(cDSApp::msDepthButton);

	//Initialize Positions
	 //Title
	if(mTitleSprite.GetDimensionX() <= cDSApp::msScreenWidth)
	{
		mTitleSprite.SetPosition((cDSApp::msScreenWidth - mTitleSprite.GetDimensionX()) / 2, mTitleSprite.GetDimensionY() / 8);
	}
	else
	{
		mTitleSprite.SetPosition(0, 0);
	}
}

//----------------------------------------------------------------------------------------------------
//Deconstructor
//----------------------------------------------------------------------------------------------------

cDSRoomMainMenu::~cDSRoomMainMenu()
{
	//Buttons
	 //Start
	if(mpButtonStart)
	{
		delete mpButtonStart;
		mpButtonStart = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}
	 //Options
	if(mpButtonOptions)
	{
		delete mpButtonOptions;
		mpButtonOptions = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}
}

//----------------------------------------------------------------------------------------------------
//General Member Functions
//----------------------------------------------------------------------------------------------------

void cDSRoomMainMenu::RunPhysics()
{
	//Buttons
	mpButtonStart->Update(CDXInput::Get()->GetMouseScreenX(), CDXInput::Get()->GetMouseScreenY(), CDXInput::Get()->IsMouseDown(0));
	mpButtonOptions->Update(CDXInput::Get()->GetMouseScreenX(), CDXInput::Get()->GetMouseScreenY(), CDXInput::Get()->IsMouseDown(0));
}

//----------------------------------------------------------------------------------------------------

int cDSRoomMainMenu::CheckRoomChange()
{
	if(mpButtonStart->GetButtonState() == kClick)
	{
		return Room::kRoomLevelOne;
	}
	else if(mpButtonOptions->GetButtonState() == kClick)
	{
		return Room::kRoomOptions;
	}
	else
	{
		return -1;
	}
}

//----------------------------------------------------------------------------------------------------

void cDSRoomMainMenu::Render()
{
	//Background
	cDSRoom::Render();
	//Buttons
	if(mpButtonStart)
	{
		mpButtonStart->Render();
	}
	if(mpButtonOptions)
	{
		mpButtonOptions->Render();
	}
	//Graphics
	mTitleSprite.Render();
}
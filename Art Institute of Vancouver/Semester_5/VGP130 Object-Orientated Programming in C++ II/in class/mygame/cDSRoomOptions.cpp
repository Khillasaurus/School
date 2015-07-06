//====================================================================================================
//File:			cDSRoomOptions.cpp
//Created:		2012/09/06
//Copyright:	Daniel Schenker
//====================================================================================================

//====================================================================================================
//Includes
//====================================================================================================

//Precompiled headers
#include "stdafx.h"

//SGE
#include "Input/Input.h"
#include "Graphics/CFont.h"

//Daniel Schenker
#include "cDSRoomOptions.h"
#include "cDSApp.h"
#include "cDSBoard.h"
#include "cDSPiece.h"
#include "cDSBitmap24bit.h"

//====================================================================================================
//Class Definitions
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//Constuctors
//----------------------------------------------------------------------------------------------------

cDSRoomOptions::cDSRoomOptions(const char* bgTexture, cDSApp* app) : cDSRoom(bgTexture)
,	mChoiceSliderDefaultX(0)
,	mChoiceSliderDefaultY(0)
,	mChoiceSliderUserX(0)
,	mChoiceSliderUserY(0)
,	pApp(app)
{
	//Create Objects
	 //Buttons
	mpButtonBack = new cDSMenuButton((cDSApp::msScreenWidth * 0.9) - (168 / 2), (cDSApp::msScreenHeight * 0.9) - (64 / 2), 168, 64, "./Resources/Textures/Buttons/back_up.png", "./Resources/Textures/Buttons/back_hover.png", "./Resources/Textures/Buttons/back_down.png", "./Resources/Textures/Buttons/back_click.png", false, cDSApp::msDepthButton);
	  //Puzzles
	   //Default
	    //image
	mpButtonPuzzleDefaultImage = new cDSMenuButton((cDSApp::msScreenWidth / 3) - (0.5 * 300), (cDSApp::msScreenHeight / 2) - (0.5 * 300), 300, 300, "./Resources/Textures/Objects/puzzledefault.bmp", "./Resources/Textures/Objects/puzzledefault.bmp", "./Resources/Textures/Objects/puzzledefault.bmp", "./Resources/Textures/Objects/puzzledefault.bmp", false, cDSApp::msDepthButton);
	    //label
	mpButtonPuzzleDefaultLabel = new cDSMenuButton(mpButtonPuzzleDefaultImage->GetOriginX() + (mpButtonPuzzleDefaultImage->GetWidth() / 2) - (200 / 2), mpButtonPuzzleDefaultImage->GetOriginY() - 90, 200, 80, "./Resources/Textures/Buttons/labelDefault_up.png", "./Resources/Textures/Buttons/labelDefault_hover.png", "./Resources/Textures/Buttons/labelDefault_down.png", "./Resources/Textures/Buttons/labelDefault_click.png", false, cDSApp::msDepthButton);
	   //User
	    //image
	mpButtonPuzzleUserImage = new cDSMenuButton((cDSApp::msScreenWidth * 2 / 3) - (0.5 * 300), (cDSApp::msScreenHeight / 2) - (0.5 * 300), 300, 300, "./Resources/Textures/Objects/puzzleuser.bmp", "./Resources/Textures/Objects/puzzleuser.bmp", "./Resources/Textures/Objects/puzzleuser.bmp", "./Resources/Textures/Objects/puzzleuser.bmp", false, cDSApp::msDepthButton);
	    //image
	mpButtonPuzzleUserLabel = new cDSMenuButton(mpButtonPuzzleUserImage->GetOriginX() + (mpButtonPuzzleUserImage->GetWidth() / 2) - (200 / 2), mpButtonPuzzleUserImage->GetOriginY() - 90, 200, 80, "./Resources/Textures/Buttons/labelUser_up.png", "./Resources/Textures/Buttons/labelUser_hover.png", "./Resources/Textures/Buttons/labelUser_down.png", "./Resources/Textures/Buttons/labelUser_click.png", false, cDSApp::msDepthButton);
	   //Choice Slider
	mChoiceSliderDefaultX = mpButtonPuzzleDefaultImage->GetOriginX() + ((mpButtonPuzzleDefaultImage->GetWidth() - 280) / 2);
	mChoiceSliderDefaultY = mpButtonPuzzleDefaultImage->GetOriginY() + (mpButtonPuzzleDefaultImage->GetHeight() * 1.1);
	mChoiceSliderUserX = mpButtonPuzzleUserImage->GetOriginX() + ((mpButtonPuzzleUserImage->GetWidth() - 280) / 2);
	mChoiceSliderUserY = mpButtonPuzzleUserImage->GetOriginY() + (mpButtonPuzzleUserImage->GetHeight() * 1.1);
	mpButtonChoiceSlider = new cDSMenuButton(mChoiceSliderDefaultX, mChoiceSliderDefaultY, 280, 20, "./Resources/Textures/Buttons/choiceSlider.bmp", "./Resources/Textures/Buttons/choiceSlider.bmp", "./Resources/Textures/Buttons/choiceSlider.bmp", "./Resources/Textures/Buttons/choiceSlider.bmp", false, cDSApp::msDepthButton);
	   //Arrows
	mpButtonRowsArrowUp = new cDSMenuButton(16, mpButtonChoiceSlider->GetOriginY() + mpButtonChoiceSlider->GetHeight(), 32, 32, "./Resources/Textures/Buttons/arrowUp_up.png", "./Resources/Textures/Buttons/arrowUp_hover.png", "./Resources/Textures/Buttons/arrowUp_down.png", "./Resources/Textures/Buttons/arrowUp_down.png", false, cDSApp::msDepthButton);
	mpButtonRowsArrowDown = new cDSMenuButton(16, mpButtonChoiceSlider->GetOriginY() + mpButtonChoiceSlider->GetHeight() + 34, 32, 32, "./Resources/Textures/Buttons/arrowDown_up.png", "./Resources/Textures/Buttons/arrowDown_hover.png", "./Resources/Textures/Buttons/arrowDown_down.png", "./Resources/Textures/Buttons/arrowDown_down.png", false, cDSApp::msDepthButton);
	mpButtonColumnsArrowUp = new cDSMenuButton(16, mpButtonChoiceSlider->GetOriginY() + mpButtonChoiceSlider->GetHeight() + 68, 32, 32, "./Resources/Textures/Buttons/arrowUp_up.png", "./Resources/Textures/Buttons/arrowUp_hover.png", "./Resources/Textures/Buttons/arrowUp_down.png", "./Resources/Textures/Buttons/arrowUp_down.png", false, cDSApp::msDepthButton);
	mpButtonColumnsArrowDown = new cDSMenuButton(16, mpButtonChoiceSlider->GetOriginY() + mpButtonChoiceSlider->GetHeight() + 102, 32, 32, "./Resources/Textures/Buttons/arrowDown_up.png", "./Resources/Textures/Buttons/arrowDown_hover.png", "./Resources/Textures/Buttons/arrowDown_down.png", "./Resources/Textures/Buttons/arrowDown_down.png", false, cDSApp::msDepthButton);

	 //Graphics
	  //Title
	mTitleTexture.Load("./Resources/Textures/Graphics/roomOptionsTitle.png");
	mTitleSprite.AddTexture(&mTitleTexture);
	mTitleSprite.SetDepth(cDSApp::msDepthButton);
	  //User puzzle instructions
	mInstructionsTexture.Load("./Resources/Textures/Graphics/roomOptionsInstructions_v6.png");
	mInstructionsSprite.AddTexture(&mInstructionsTexture);
	mInstructionsSprite.SetDepth(cDSApp::msDepthButton);

	//Fonts
	mFontRows.Create(FontType::IMPACT, 64);
	mFontColumns.Create(FontType::IMPACT, 64);
	mFontRows.SetColor(25, 155, 144);
	mFontColumns.SetColor(25, 155, 144);

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
	 //User Puzzle Instructions
	//mInstructionsSprite.SetPosition(mpButtonPuzzleUserImage->GetOriginX() + ((mpButtonPuzzleUserImage->GetWidth() - 400) / 2), mpButtonChoiceSlider->GetOriginY() + (mpButtonChoiceSlider->GetHeight() * 2));
	mInstructionsSprite.SetPosition((cDSApp::msScreenWidth - 700) / 2, mpButtonChoiceSlider->GetOriginY() + (mpButtonChoiceSlider->GetHeight() * 2));
	 //Choice Slider
	if(pApp->GetPuzzleInUse() == 0)
	{
		mpButtonChoiceSlider->SetOrigin(mChoiceSliderDefaultX, mChoiceSliderDefaultY);
	}
	else if(pApp->GetPuzzleInUse() == 1)
	{
		mpButtonChoiceSlider->SetOrigin(mChoiceSliderUserX, mChoiceSliderUserY);
	}
}

//----------------------------------------------------------------------------------------------------
//Deconstructor
//----------------------------------------------------------------------------------------------------

cDSRoomOptions::~cDSRoomOptions()
{
	//Objects
	 //Buttons
	  //Back
	if(mpButtonBack)
	{
		delete mpButtonBack;
		mpButtonBack = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}
	  //Puzzles
	   //Default
	    //Image
	if(mpButtonPuzzleDefaultImage)
	{
		delete mpButtonPuzzleDefaultImage;
		mpButtonPuzzleDefaultImage = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}
	    //Label
	if(mpButtonPuzzleDefaultLabel)
	{
		delete mpButtonPuzzleDefaultLabel;
		mpButtonPuzzleDefaultLabel = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}
	   //User
	    //Image
	if(mpButtonPuzzleUserImage)
	{
		delete mpButtonPuzzleUserImage;
		mpButtonPuzzleUserImage = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}
	    //Label
	if(mpButtonPuzzleUserLabel)
	{
		delete mpButtonPuzzleUserLabel;
		mpButtonPuzzleUserLabel = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}
	  //Choice Slider
	if(mpButtonChoiceSlider)
	{
		delete mpButtonChoiceSlider;
		mpButtonChoiceSlider = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}
	  //Arrows
	if(mpButtonRowsArrowUp)
	{
		delete mpButtonRowsArrowUp;
		mpButtonRowsArrowUp = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}
	if(mpButtonRowsArrowDown)
	{
		delete mpButtonRowsArrowDown;
		mpButtonRowsArrowDown = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}
	if(mpButtonColumnsArrowUp)
	{
		delete mpButtonColumnsArrowUp;
		mpButtonColumnsArrowUp = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}
	if(mpButtonColumnsArrowDown)
	{
		delete mpButtonColumnsArrowDown;
		mpButtonColumnsArrowDown = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}

	//Fonts
	mFontRows.Destroy();
	mFontColumns.Destroy();
}

//----------------------------------------------------------------------------------------------------
//General Member Functions
//----------------------------------------------------------------------------------------------------

void cDSRoomOptions::RunPhysics()
{
	//Objects
	 //Buttons
	mpButtonBack->Update(CDXInput::Get()->GetMouseScreenX(), CDXInput::Get()->GetMouseScreenY(), CDXInput::Get()->IsMouseDown(0));
	  //Puzzles
	   //Default
	    //image
	mpButtonPuzzleDefaultImage->Update(CDXInput::Get()->GetMouseScreenX(), CDXInput::Get()->GetMouseScreenY(), CDXInput::Get()->IsMouseDown(0));
	    //label
	mpButtonPuzzleDefaultLabel->Update(CDXInput::Get()->GetMouseScreenX(), CDXInput::Get()->GetMouseScreenY(), CDXInput::Get()->IsMouseDown(0));
	   //User
	    //image
	mpButtonPuzzleUserImage->Update(CDXInput::Get()->GetMouseScreenX(), CDXInput::Get()->GetMouseScreenY(), CDXInput::Get()->IsMouseDown(0));
	    //label
	mpButtonPuzzleUserLabel->Update(CDXInput::Get()->GetMouseScreenX(), CDXInput::Get()->GetMouseScreenY(), CDXInput::Get()->IsMouseDown(0));
	  //Choice Slider
	mpButtonChoiceSlider->Update(CDXInput::Get()->GetMouseScreenX(), CDXInput::Get()->GetMouseScreenY(), CDXInput::Get()->IsMouseDown(0));
	  //Arrows
	mpButtonRowsArrowUp->Update(CDXInput::Get()->GetMouseScreenX(), CDXInput::Get()->GetMouseScreenY(), CDXInput::Get()->IsMouseDown(0));
	mpButtonRowsArrowDown->Update(CDXInput::Get()->GetMouseScreenX(), CDXInput::Get()->GetMouseScreenY(), CDXInput::Get()->IsMouseDown(0));
	mpButtonColumnsArrowUp->Update(CDXInput::Get()->GetMouseScreenX(), CDXInput::Get()->GetMouseScreenY(), CDXInput::Get()->IsMouseDown(0));
	mpButtonColumnsArrowDown->Update(CDXInput::Get()->GetMouseScreenX(), CDXInput::Get()->GetMouseScreenY(), CDXInput::Get()->IsMouseDown(0));

	//Choose puzzle background
	 //Default
	if(pApp->GetPuzzleInUse() != 0)
	{
		if((mpButtonPuzzleDefaultImage->GetButtonState() == kClick) || (mpButtonPuzzleDefaultLabel->GetButtonState() == kClick))
		{
			pApp->SetPuzzleInUse(0);
		}
	}
	 //User
	if(pApp->GetPuzzleInUse() != 1)
	{
		if((mpButtonPuzzleUserImage->GetButtonState() == kClick) || (mpButtonPuzzleUserLabel->GetButtonState() == kClick))
		{
			//if the user puzzle exists
			FILE* fpBitmap = fopen("../../puzzle.bmp", "rb");
			if(fpBitmap)
			{
				fclose(fpBitmap);
				pApp->SetPuzzleInUse(1);
			}
			else
			{
				pApp->SetPuzzleInUse(0);
			}
		}
	}
	 //Choice Slider
	if(mpButtonChoiceSlider->GetButtonState() == kClick)
	{
		if(pApp->GetPuzzleInUse() == 0)
		{
			pApp->SetPuzzleInUse(1);
		}
		else if(pApp->GetPuzzleInUse() == 1)
		{
			pApp->SetPuzzleInUse(0);
		}
	}
	 //Arrows
	if(mpButtonRowsArrowUp->GetButtonState() == kClick)
	{
		++pApp->mRows;
	}
	if(mpButtonRowsArrowDown->GetButtonState() == kClick)
	{
		if(pApp->mRows > 3)
		{
			--pApp->mRows;
		}
	}
	if(mpButtonColumnsArrowUp->GetButtonState() == kClick)
	{
		++pApp->mColumns;
	}
	if(mpButtonColumnsArrowDown->GetButtonState() == kClick)
	{
		if(pApp->mColumns > 3)
		{
			--pApp->mColumns;
		}
	}

	//Update choice slider position
	if(pApp->GetPuzzleInUse() == 0)
	{
		mpButtonChoiceSlider->SetOrigin(mChoiceSliderDefaultX, mChoiceSliderDefaultY);
	}
	else if(pApp->GetPuzzleInUse() == 1)
	{
		mpButtonChoiceSlider->SetOrigin(mChoiceSliderUserX, mChoiceSliderUserY);
	}

	//Update fonts
	sprintf_s(mRowsBuff, "Rows: %d", pApp->mRows);
	sprintf_s(mColumnsBuff, "Columns: %d", pApp->mColumns);
}

//----------------------------------------------------------------------------------------------------

int cDSRoomOptions::CheckRoomChange()
{
	if(mpButtonBack->GetButtonState() == kClick)
	{
		return Room::kRoomMainMenu;
	}
	else
	{
		return -1;
	}
}

//----------------------------------------------------------------------------------------------------

void cDSRoomOptions::Render()
{
	//background
	cDSRoom::Render();
	//Buttons
	 //Back
	if(mpButtonBack)
	{
		mpButtonBack->Render();
	}
	 //Puzzle
	  //Default
	   //Image
	if(mpButtonPuzzleDefaultImage)
	{
		mpButtonPuzzleDefaultImage->Render();
	}
	   //Label
	if(mpButtonPuzzleDefaultLabel)
	{
		mpButtonPuzzleDefaultLabel->Render();
	}
	  //User
	   //Image
	if(mpButtonPuzzleUserImage)
	{
		mpButtonPuzzleUserImage->Render();
	}
	   //Label
	if(mpButtonPuzzleUserLabel)
	{
		mpButtonPuzzleUserLabel->Render();
	}
	 //Choice Slider
	if(mpButtonChoiceSlider)
	{
		mpButtonChoiceSlider->Render();
	}
	 //Arrows
	if(mpButtonRowsArrowUp)
	{
		mpButtonRowsArrowUp->Render();
	}
	if(mpButtonRowsArrowDown)
	{
		mpButtonRowsArrowDown->Render();
	}
	if(mpButtonColumnsArrowUp)
	{
		mpButtonColumnsArrowUp->Render();
	}
	if(mpButtonColumnsArrowDown)
	{
		mpButtonColumnsArrowDown->Render();
	}

	//Graphics
	 //title
	mTitleSprite.Render();
	 //User Puzzle Instructions
	if(pApp->GetPuzzleInUse() == 1)
	{
		mInstructionsSprite.Render();
	}

	//Fonts
	mFontRows.PrintText(mRowsBuff, mpButtonRowsArrowUp->GetOriginX() + mpButtonRowsArrowUp->GetWidth() + 4, mpButtonRowsArrowUp->GetOriginY() + 1);
	mFontColumns.PrintText(mColumnsBuff, mpButtonColumnsArrowUp->GetOriginX() + mpButtonColumnsArrowUp->GetWidth() + 4, mpButtonColumnsArrowUp->GetOriginY() + 1);
}
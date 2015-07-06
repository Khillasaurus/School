//====================================================================================================
//File:			cDSApp.cpp
//Created:		2012/07/26
//Copyright:	Daniel Schenker
//====================================================================================================

//====================================================================================================
//Includes
//====================================================================================================

//Precompiled headers
#include "stdafx.h"

//SGE
//#include "Audio/Audio.h"
#include "Input/Input.h"
//#include "Misc/Misc.h"
//#include "Resource/Resource.h"
#include "Utility/Utility.h"
#include "SGE.h"

//Daniel Schenker
#include "cDSApp.h"
#include "cDSCursor.h"
#include "cDSRoomMainMenu.h"
#include "cDSRoomOptions.h"
#include "cDSRoomLevel1.h"
#include "cDSBitmap24bit.h"
#include "cDSPiece.h"
#include "cDSBoard.h"

//====================================================================================================
//Statics
//====================================================================================================

const int cDSApp::msScreenWidth = 1280;
const int cDSApp::msScreenHeight = 720;
float cDSApp::msDepthBackground = 1.0f;
float cDSApp::msDepthObject = 0.5f;
float cDSApp::msDepthButton = 0.25f;
float cDSApp::msDepthCursor = 0.0f;

//====================================================================================================
//Class Definitions
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//Constuctors
//----------------------------------------------------------------------------------------------------

cDSApp::cDSApp()
:	mRows(3)
,	mColumns(4)
,	mpRoomMainMenu(NULL)//Switch NULL for nullptr when using visual studio 2010 or newer
,	mpRoomOptions(NULL)//Switch NULL for nullptr when using visual studio 2010 or newer
,	mpRoomLevel1(NULL)//Switch NULL for nullptr when using visual studio 2010 or newer
,	mPuzzleInUse(0)
,	mPuzzleDimensionX(0)
,	mPuzzleDimensionY(0)
{
}

//----------------------------------------------------------------------------------------------------

cDSApp::cDSApp(const int screenWidth, const int screenHeight)
:	mRows(3)
,	mColumns(4)
,	mpRoomMainMenu(NULL)//Switch NULL for nullptr when using visual studio 2010 or newer
,	mpRoomOptions(NULL)//Switch NULL for nullptr when using visual studio 2010 or newer
,	mpRoomLevel1(NULL)//Switch NULL for nullptr when using visual studio 2010 or newer
,	mPuzzleInUse(0)
,	mPuzzleDimensionX(0)
,	mPuzzleDimensionY(0)
{
}

//----------------------------------------------------------------------------------------------------
//General Member Functions
//----------------------------------------------------------------------------------------------------

//1. Game initalization
void cDSApp::OnInitialize(void)
{
	//const int iWinWidth = screenWidth;//CIniFile::Get()->GetInt("WinWidth", 800);
	//const int iWinHeight = screenHeight;//CIniFile::Get()->GetInt("WinHeight", 600);
	//const int iResourceLimit = CIniFile::Get()->GetInt("ResourceLimit", 100);
	const bool kFullscreen = false;//CIniFile::Get()->GetBool("Fullscreen", false);

	//Initialize all engine systems
	CTimer::Get()->Initialize();
	CDXGraphics::Get()->Initialize(mWindow, cDSApp::msScreenWidth, cDSApp::msScreenHeight, kFullscreen);
	//CDXGraphics::Get()->Initialize(mWindow, iWinWidth, iWinHeight, bFullscreen);
	CSpriteRenderer::Get()->Initialize();
	CDXInput::Get()->Initialize(mWindow);
	//CResourceManager::Get()->Initialize(iResourceLimit);
	//CFMOD::Get()->Initialize(100);
	Random::SetRandSeed(-1);//Random::SetRandSeed();

	//Debug initialization
	//if (CIniFile::Get()->GetBool("Debug", false))
	//{
	//	Debug::Initialize();
	//}
	//Create a debug log for writing, or overwrite the old one if it exists
	FILE* fpDebugLog = fopen("./debuglog.txt", "w");
	fclose(fpDebugLog);

	//Create a new font
	mDefaultFont.Create(FontType::GARAMOND);
	#ifdef DSDEBUGMODE
		mFontDebug1.Create(FontType::GARAMOND);
		mFontDebug2.Create(FontType::GARAMOND);
		mFontDebug3.Create(FontType::GARAMOND);
	#endif //DSDEBUGMODE
	//User init logic
	//SGE_Initialize();
		
	//Load
	 //Tools
	 //HUD
	  //Cursor
	mpCursor = new cDSCursor(4, 4, "./Resources/Textures/Cursor/cursorNormal_v2.png", "./Resources/Textures/Cursor/cursorClick_v2.png", cDSApp::msDepthCursor, false);
	
	//Set initial values
	 //General Variables
	mRoomNumber = 0;
}

//----------------------------------------------------------------------------------------------------

//2. Main game loop
void cDSApp::OnMainLoop(void)
{
	//Update timer
	CTimer::Get()->Update();
	float fSeconds = CTimer::Get()->GetElapsedSeconds();

	//Gather input
	CDXInput::Get()->Update();
	mpCursor->Update();

	//Update sound
	//CFMOD::Get()->Update();

	//User update logic
	//Quit Button
	if(SGE::Input_IsKeyDown(SGE::Keys::ESCAPE))
	{
		Quit();
		return;
	}

	//if( mpMyGame )
	//{
	//	mpSimulator->Update(fSeconds);
	//}
	//else
	//{
	//	mpMyFrontEnd->Update(fSeconds);
	//}

	//myRenderer->Update();

	//Begin scene
	CDXGraphics::Get()->BeginRender();

	//Begin sprite rendering
	CSpriteRenderer::Get()->BeginRender();

	//User render logic
	 //HUD
	  //Cursor
	mpCursor->Render();
	#ifdef DSDEBUGMODE
		//Choose room
		 //0
		if(SGE::Input_IsKeyDown(SGE::Keys::ZERO))
		{
			mRoomNumber = 0;
		}
		else if(SGE::Input_IsKeyDown(SGE::Keys::ONE))
		{
			mRoomNumber = 1;
		}
		else if(SGE::Input_IsKeyDown(SGE::Keys::TWO))
		{
			mRoomNumber = 2;
		}

		//draw the mouse coordinates to the screen
		 //X
		char mouseXTextBuff[64];
		mDefaultFont.SetColor(25, 155, 144);
		sprintf_s(mouseXTextBuff, "Mouse X: %d", CDXInput::Get()->GetMouseScreenX());
		mDefaultFont.PrintText(mouseXTextBuff, 0, 32);
		 //Y
		char mouseYTextBuff[64];
		mDefaultFont.SetColor(25, 155, 144);
		sprintf_s(mouseYTextBuff, "Mouse Y: %d", CDXInput::Get()->GetMouseScreenY());
		mDefaultFont.PrintText(mouseYTextBuff, 0, 64);

		  //Render FPS
		const bool bFPS = true;//CIniFile::Get()->GetBool("FPS", false);
		if(bFPS)
		{
			char temp[64];
			mDefaultFont.SetColor(255, 255, 0);
			sprintf_s(temp, "FPS: %f", CTimer::Get()->GetFPS());
			mDefaultFont.PrintText(temp, 0, 0);
		}

		/*///
		if(mpBoard)
		{
			//Debug
			 //1
			mFontDebug1.SetColor(255, 255, 0);
			sprintf_s(debugBuff1, "Move Counter: %d", mpBoard->mMoveCounter);
			mFontDebug1.PrintText(debugBuff1, GetScreenWidth() - 384, 0);
			 //2
			mFontDebug2.SetColor(255, 255, 0);
			sprintf_s(debugBuff2, "mTest: %d", mTest);
			mFontDebug2.PrintText(debugBuff2, GetScreenWidth() - 384, 32);
			 //3
			mFontDebug3.SetColor(255, 255, 0);
			sprintf_s(debugBuff3, "mPuzzleInUse: %d", mPuzzleInUse);
			mFontDebug3.PrintText(debugBuff3, GetScreenWidth() - 384, 64);
		}
		*////
	#endif //DSDEBUGMODE

	//Room specifics
	 //Main Menu
	if(mRoomNumber == Room::kRoomMainMenu)
	{
		if(!mpRoomMainMenu)
		{
			mpRoomMainMenu = new cDSRoomMainMenu("./Resources/Textures/Backgrounds/bgMainMenu.png");
		}
		//else run main loop
		else
		{
			mpRoomMainMenu->RunPhysics();

			//Check if we need to change rooms
			int newRoomNum = mpRoomMainMenu->CheckRoomChange();
			//Do NOT change rooms
			if(newRoomNum < 0)
			{
				mpRoomMainMenu->Render();
			}
			 //Options
			else if(newRoomNum == Room::kRoomOptions)
			{
				mRoomNumber = Room::kRoomOptions;
			}
			 //LevelOne
			else if(newRoomNum == Room::kRoomLevelOne)
			{
				mRoomNumber = Room::kRoomLevelOne;
			}

			//if we decided to change rooms, release uneeded resources
			if(newRoomNum >= 0)
			{
				delete mpRoomMainMenu;
				mpRoomMainMenu = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
			}
		}
	}
	else if(mRoomNumber == Room::kRoomOptions)
	{
		if(!mpRoomOptions)
		{
			mpRoomOptions = new cDSRoomOptions("./Resources/Textures/Backgrounds/bgOptions.jpg", this);
		}
		//else run main loop
		else
		{
			mpRoomOptions->RunPhysics();

			//Check if we need to change rooms
			int newRoomNum = mpRoomOptions->CheckRoomChange();
			//Do NOT change rooms
			if(newRoomNum < 0)
			{
				mpRoomOptions->Render();
			}
			 //Main Menu
			else if(newRoomNum == Room::kRoomMainMenu)
			{
				mRoomNumber = Room::kRoomMainMenu;
			}

			//if we decided to change rooms, release uneeded resources
			if(newRoomNum >= 0)
			{
				delete mpRoomOptions;
				mpRoomOptions = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
			}
		}
	}
	else if(mRoomNumber == Room::kRoomLevelOne)
	{
		if(!mpRoomLevel1)
		{
			mpRoomLevel1 = new cDSRoomLevel1("./Resources/Textures/Backgrounds/pixelated.bmp", mPuzzleInUse, mRows, mColumns);
		}
		//else run main loop
		else
		{
			mpRoomLevel1->RunPhysics();

			//Check if we need to change rooms
			int newRoomNum = mpRoomLevel1->CheckRoomChange();
			//Do NOT change rooms
			if(newRoomNum < 0)
			{
				mpRoomLevel1->Render();
			}
			 //LevelOne
			else if(newRoomNum == Room::kRoomMainMenu)
			{
				mRoomNumber = Room::kRoomMainMenu;
			}

			//if we decided to change rooms, release uneeded resources
			if(newRoomNum >= 0)
			{
				delete mpRoomLevel1;
				mpRoomLevel1 = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
			}
		}
	}

	//End sprite rendering
	CSpriteRenderer::Get()->EndRender();

	//Debug render
	//if(CIniFile::Get()->GetBool("Debug", false))
	//{
	//	Debug::Render();
	//}

	//End scene
	CDXGraphics::Get()->EndRender();
}

//----------------------------------------------------------------------------------------------------

//3. Game shutdown
void cDSApp::OnTerminate(void)
{
	//User clean up logic
	//Unload

	 //General
	//SGE_Terminate();

	 //Rooms
	  //Main Menu
	if(mpRoomMainMenu)
	{
		delete mpRoomMainMenu;
		mpRoomMainMenu = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}
	  //Options
	if(mpRoomOptions)
	{
		delete mpRoomOptions;
		mpRoomOptions = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}
	  //Level1
	if(mpRoomLevel1)
	{
		delete mpRoomLevel1;
		mpRoomLevel1 = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}

	 //HUD
	  //Cursor
	if(mpCursor)
	{
		delete mpCursor;
		mpCursor = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}

	//Destroy the font
	#ifdef DSDEBUGMODE
		mFontDebug1.Destroy();
		mFontDebug2.Destroy();
		mFontDebug3.Destroy();
	#endif //DSDEBUGMODE
	mDefaultFont.Destroy();

	//Debug termination
	//if (CIniFile::Get()->GetBool("Debug", false))
	//{
	//	Debug::Terminate();
	//}

	//Shutdown all engine systems
	//CFMOD::Get()->Terminate();
	//CResourceManager::Get()->Terminate();
	CDXInput::Get()->Terminate();
	CSpriteRenderer::Get()->Terminate();
	CDXGraphics::Get()->Terminate();
	CTimer::Get()->Terminate();
}

//----------------------------------------------------------------------------------------------------
//Getters
//----------------------------------------------------------------------------------------------------

D3DXVECTOR2 cDSApp::GetScreenSize() const
{
	//Convert origin data to the D3DXVECTOR2 format
	D3DXVECTOR2 size(static_cast<float>(cDSApp::msScreenWidth), static_cast<float>(cDSApp::msScreenHeight));

	return size;
}

//----------------------------------------------------------------------------------------------------

int cDSApp::GetScreenWidth() const
{
	return cDSApp::msScreenWidth;
}

//----------------------------------------------------------------------------------------------------

int cDSApp::GetScreenHeight() const
{
	return cDSApp::msScreenHeight;
}

//----------------------------------------------------------------------------------------------------

int cDSApp::GetRoomNumber() const
{
	return mRoomNumber;
}

//----------------------------------------------------------------------------------------------------

int cDSApp::GetPuzzleInUse() const
{
	return mPuzzleInUse;
}

//----------------------------------------------------------------------------------------------------
//Setters
//----------------------------------------------------------------------------------------------------

void cDSApp::SetRoomNumber(const int roomNumber)
{
	mRoomNumber = roomNumber;
}

//----------------------------------------------------------------------------------------------------
	
void cDSApp::SetPuzzleInUse(int puzzleInUse)
{
	mPuzzleInUse = puzzleInUse;
}
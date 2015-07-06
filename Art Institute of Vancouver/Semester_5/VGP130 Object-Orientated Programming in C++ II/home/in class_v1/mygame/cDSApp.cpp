//====================================================================================================
// File:		cDSApp.cpp
// Created:		2012/07/26
// Copyright:	Daniel Schenker
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "stdafx.h"
#include "cDSApp.h"
//#include "Audio/Audio.h"
#include "Core/Core.h"
#include "Graphics/Graphics.h"
#include "Input/Input.h"
//#include "Misc/Misc.h"
//#include "Resource/Resource.h"
#include "Utility/Utility.h"
#include "SGE.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

// 1. Game initalization
void cDSApp::OnInitialize(void)
{
	const int iWinWidth = 800;//CIniFile::Get()->GetInt("WinWidth", 800);
	const int iWinHeight = 600;//CIniFile::Get()->GetInt("WinHeight", 600);
	//const int iResourceLimit = CIniFile::Get()->GetInt("ResourceLimit", 100);
	const bool bFullscreen = false;//CIniFile::Get()->GetBool("Fullscreen", false);

	// Initialize all engine systems
	CTimer::Get()->Initialize();
	CDXGraphics::Get()->Initialize(mWindow, iWinWidth, iWinHeight, bFullscreen);
	CSpriteRenderer::Get()->Initialize();
	CDXInput::Get()->Initialize(mWindow);
	//CResourceManager::Get()->Initialize(iResourceLimit);
	//CFMOD::Get()->Initialize(100);
	Random::SetRandSeed();

	// Debug initialization
	//if (CIniFile::Get()->GetBool("Debug", false))
	//{
	//	Debug::Initialize();
	//}

	// Create a new font
	mFont.Create(FontType::GARAMOND);
	mFont.SetColor(255, 255, 0);

	// User init logic
	//SGE_Initialize();

	//Test: Draw a Sprite
	mTestTexture.Load("./Resources/testSmileyFace.png");
	mTestSprite.AddTexture(&mTestTexture);
}

//----------------------------------------------------------------------------------------------------

// 2. Main game loop
void cDSApp::OnMainLoop(void)
{
	// a. Front-end initialization
	cDSApp::FrontEndInitialize();

	// b. Front-end loop
	cDSApp::FrontEndLoop();

		// i. Gather input
		cDSApp::FrontEndLoopInput();

		// ii. Render Screen
		cDSApp::FrontEndLoopRender();

		// iii. Update front-end state
		cDSApp::FrontEndLoopUpdateState();

		// iv. Trigger any state changes
		cDSApp::FrontEndLoopTriggerState();

	//c. Front-end shutdown
	cDSApp::FrontEndShutdown();

	//d. Level initialization
	cDSApp::LevelInitialization();

	//e. Level game loop
	cDSApp::LevelLoop();

		//i. Gather input
		cDSApp::LevelLoopInput();

		//ii. Run AI
		cDSApp::LevelLoopAI();

		//iii. Run physics simulations
		cDSApp::LevelLoopPhysics();

		//iv. Update game entities
		cDSApp::LevelLoopUpdateEntities();

		//v. Send/Receive network messages
		cDSApp::LevelLoopNetwork();

		//vi. Update time step
		cDSApp::LevelLoopUpdateTimestep();

		//vii. Update game state
		cDSApp::LevelLoopUpdateState();

	//f. Level Shutdown
	cDSApp::LevelShutdown();
}

//----------------------------------------------------------------------------------------------------

// a. Front-end initialization
void cDSApp::FrontEndInitialize()
{
}

//----------------------------------------------------------------------------------------------------

// b. Front-end loop
void cDSApp::FrontEndLoop()
{
}

//----------------------------------------------------------------------------------------------------

// i. Gather input
void cDSApp::FrontEndLoopInput()
{
	CDXInput::Get()->Update();
}

//----------------------------------------------------------------------------------------------------

// ii. Render Screen
void cDSApp::FrontEndLoopRender()
{
	// Update sound
	//CFMOD::Get()->Update();
}

//----------------------------------------------------------------------------------------------------

// iii. Update front-end state
void cDSApp::FrontEndLoopUpdateState()
{
	// Update timer
	CTimer::Get()->Update();
	float fSeconds = CTimer::Get()->GetElapsedSeconds();
}

//----------------------------------------------------------------------------------------------------

// iv. Trigger any state changes
void cDSApp::FrontEndLoopTriggerState()
{
	// Quit Button
	if(SGE::Input_IsKeyDown(SGE::Keys::ESCAPE))
	{
		Quit();
		return;
	}
}

//----------------------------------------------------------------------------------------------------

// c. Front-end shutdown
void cDSApp::FrontEndShutdown()
{
}

//----------------------------------------------------------------------------------------------------

//d. Level initialization
void cDSApp::LevelInitialization()
{
	// Begin scene
	CDXGraphics::Get()->BeginRender();

	// Begin sprite rendering
	CSpriteRenderer::Get()->BeginRender();
}

//----------------------------------------------------------------------------------------------------

// e. Level game loop
void cDSApp::LevelLoop()
{
}

//----------------------------------------------------------------------------------------------------

// i. Gather input
void cDSApp::LevelLoopInput()
{
}

//----------------------------------------------------------------------------------------------------

// ii. Run AI
void cDSApp::LevelLoopAI()
{
}

//----------------------------------------------------------------------------------------------------

// iii. Run physics simulations
void cDSApp::LevelLoopPhysics()
{
	mTestSprite.SetPosition(mTestSprite.GetPositionX() + 1, 15);
}

//----------------------------------------------------------------------------------------------------

// iv. Update game entities
void cDSApp::LevelLoopUpdateEntities()
{
}

//----------------------------------------------------------------------------------------------------

// v. Send/Receive network messages
void cDSApp::LevelLoopNetwork()
{
}

//----------------------------------------------------------------------------------------------------
// vi. Update time step
void cDSApp::LevelLoopUpdateTimestep()
{
}

//----------------------------------------------------------------------------------------------------

// vii. Update game state
void cDSApp::LevelLoopUpdateState()
{
	// User render logic

	// Draw our game objects here
	mTestSprite.Render();

	// Render FPS
	const bool bFPS = true;//CIniFile::Get()->GetBool("FPS", false);
	if (bFPS)
	{
		char temp[256];
		sprintf_s(temp, "FPS: %f", CTimer::Get()->GetFPS());
		mFont.PrintText(temp, 5, 5);
	}
}

//----------------------------------------------------------------------------------------------------

// f. Level Shutdown
void cDSApp::LevelShutdown()
{
	// End sprite rendering
	CSpriteRenderer::Get()->EndRender();

	// Debug render
	//if(CIniFile::Get()->GetBool("Debug", false))
	//{
	//	Debug::Render();
	//}

	// End scene
	CDXGraphics::Get()->EndRender();
}

//----------------------------------------------------------------------------------------------------

// 3. Game shutdown
void cDSApp::OnTerminate(void)
{
	// User clean up logic
	//SGE_Terminate();

	// Destroy the font
	mFont.Destroy();

	// Debug termination
	//if (CIniFile::Get()->GetBool("Debug", false))
	//{
	//	Debug::Terminate();
	//}

	// Shutdown all engine systems
	//CFMOD::Get()->Terminate();
	//CResourceManager::Get()->Terminate();
	CDXInput::Get()->Terminate();
	CSpriteRenderer::Get()->Terminate();
	CDXGraphics::Get()->Terminate();
	CTimer::Get()->Terminate();
}
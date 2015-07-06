//=================================================================================================
// Filename:	WinMain.cpp
// Copyright:	Daniel Schenker
// Created:		2012/10/09
// Last Edited:	2012/11/09
// Description:	Blastoids game.
//=================================================================================================

#ifndef DSDEBUGMODE
#define DSDEBUGMODE 1
#endif //#ifndef DSDEBUGMODE

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "Frontend.h"
#include "Game.h"
#include "GameContext.h"
#include "GameStates.h"

// SGE
#include <SGE.h>
using namespace SGE;

// Debug
#if DSDEBUGMODE == 1
#include "../SGE/Graphics/CFont.h"
#endif//#if DSDEBUGMODE == 1


//=================================================================================================
// Globals
//=================================================================================================

BaseState* gCurrentState = NULL;
GameState::Type gNextState = GameState::Invalid;

GameContext gGameContext;

bool gQuit = false;

// Debug
#if DSDEBUGMODE == 1
// Mouse
 // Screen
  // X
CFont gFontMouseScreenX;
char gFontMouseScreenXTextBuff[64];
  // Y
CFont gFontMouseScreenY;
char gFontMouseScreenYTextBuff[64];
// General
 // Debug 1
CFont gFontDebug1;
char gFontDebug1TextBuff[256];
 // Debug 2
CFont gFontDebug2;
char gFontDebug2TextBuff[256];
 // Debug 3
CFont gFontDebug3;
char gFontDebug3TextBuff[256];
#endif//#if DSDEBUGMODE == 1

//=================================================================================================
// Function Prototypes
//=================================================================================================

#if DSDEBUGMODE == 1
void DebugInitialize();
void DebugTerminate();
void DebugUpdate();
void DebugRender();
#endif//#if DSDEBUGMODE == 1

//=================================================================================================
// Helper Functions
//=================================================================================================

// Debug
#if DSDEBUGMODE == 1
void DebugInitialize()
{
	//Cache screen size
	const int kScreenWidth = IniFile_GetInt("WinWidth", 800);
	const int kScreenHeight = IniFile_GetInt("WinHeight", 600);
	 // Mouse
	  // Screen
	   // X
	gFontMouseScreenX.Create(FontType::GARAMOND, 24, false, false);
	gFontMouseScreenX.SetColor(25, 155, 144);
	gFontMouseScreenX.SetTextArea(0, 0, kScreenWidth, kScreenHeight);
	   // Y
	gFontMouseScreenY.Create(FontType::GARAMOND, 24, false, false);
	gFontMouseScreenY.SetColor(25, 155, 144);
	gFontMouseScreenY.SetTextArea(0, 0, kScreenWidth, kScreenHeight);
	 // General
	  // Debug 1
	gFontDebug1.Create(FontType::GARAMOND, 24, false, false);
	gFontDebug1.SetColor(150, 50, 100);
	gFontDebug1.SetTextArea(0, 0, kScreenWidth, kScreenHeight);
	gFontDebug1.SetFormat(FontFormat::RIGHT);
	  // Debug 2
	gFontDebug2.Create(FontType::GARAMOND, 24, false, false);
	gFontDebug2.SetColor(150, 50, 100);
	gFontDebug2.SetTextArea(0, 0, kScreenWidth, kScreenHeight);
	gFontDebug2.SetFormat(FontFormat::RIGHT);
	  // Debug 3
	gFontDebug3.Create(FontType::GARAMOND, 24, false, false);
	gFontDebug3.SetColor(150, 50, 100);
	gFontDebug3.SetTextArea(0, 0, kScreenWidth, kScreenHeight);
	gFontDebug3.SetFormat(FontFormat::RIGHT);
}

//-------------------------------------------------------------------------------------------------

void DebugTerminate()
{
	// Mouse
	 // Screen
	  //X
	gFontMouseScreenX.Destroy();
	  //Y
	gFontMouseScreenY.Destroy();
	// General
	 //Debug1
	gFontDebug1.Destroy();
	 //Debug2
	gFontDebug2.Destroy();
	 //Debug3
	gFontDebug3.Destroy();
}

//-------------------------------------------------------------------------------------------------

void DebugUpdate()
{
	// Mouse
	 // Screen
	  //X
	sprintf_s(gFontMouseScreenXTextBuff, "Mouse Screen X: %d", Input_GetMouseScreenX());
	  //Y
	sprintf_s(gFontMouseScreenYTextBuff, "Mouse Screen Y: %d", Input_GetMouseScreenY());
	// General
	 //Debug1
	sprintf_s(gFontDebug1TextBuff, "Temp: %d", 1);
	 //Debug2
	sprintf_s(gFontDebug2TextBuff, "Temp: %d", 2);
	 //Debug3
	sprintf_s(gFontDebug3TextBuff, "Temp: %d", 3);
}

//-------------------------------------------------------------------------------------------------

void DebugRender()
{
	// Mouse
	 // Screen
	  //X
	gFontMouseScreenX.PrintText(gFontMouseScreenXTextBuff, 0, 32);
	  //Y
	gFontMouseScreenY.PrintText(gFontMouseScreenYTextBuff, 0, 64);
	// General
	 //Debug1
	gFontDebug1.PrintText(gFontDebug1TextBuff, 0, 0);
	 //Debug2
	gFontDebug2.PrintText(gFontDebug2TextBuff, 0, 32);
	 //Debug1
	gFontDebug3.PrintText(gFontDebug3TextBuff, 0, 64);
}
#endif//#if DSDEBUGMODE == 1

//=================================================================================================
// SGE Functions
//=================================================================================================

void SGE_Initialize()
{
	gCurrentState = new Frontend(gGameContext);
	gCurrentState->Load();

	// Debug
	#if DSDEBUGMODE == 1
	DebugInitialize();
	#endif//#if DSDEBUGMODE == 1
}

//-------------------------------------------------------------------------------------------------

void SGE_Terminate()
{
	gCurrentState->Unload();
	delete gCurrentState;

	// Debug
	#if DSDEBUGMODE == 1
	DebugTerminate();
	#endif//#if DSDEBUGMODE == 1
}

//-------------------------------------------------------------------------------------------------

bool SGE_Update(float deltaTime)
{
	// Check if we need to change state
	if(gNextState != GameState::Invalid)
	{
		// Leave the current state
		if(gCurrentState != NULL)
		{
			gCurrentState->Unload();
			delete gCurrentState;
		}

		// Switch state
		switch(gNextState)
		{
		case GameState::Frontend:
			gCurrentState = new Frontend(gGameContext);
			break;
		case GameState::Game:
			gCurrentState = new Game(gGameContext);
			break;
		}

		// Enter the new state
		if(gCurrentState != NULL)
		{
			gCurrentState->Load();
		}
	}

	//Update the current state
	gNextState = static_cast<GameState::Type>(gCurrentState->Update(deltaTime));

	//Quit the application
	if(gNextState == GameState::Quit)
	{
		gQuit = true;
	}

	// Debug
	#if DSDEBUGMODE == 1
	DebugUpdate();
	#endif//#if DSDEBUGMODE == 1

	return gQuit;
}

//-------------------------------------------------------------------------------------------------

void SGE_Render()
{
	gCurrentState->Render();

	// Debug
	#if DSDEBUGMODE == 1
	DebugRender();
	#endif//#if DSDEBUGMODE == 1
}

//-------------------------------------------------------------------------------------------------
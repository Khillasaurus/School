//=================================================================================================
// Filename:	WinMain.cpp
// Copyright:	Daniel Schenker
// Created:		2012/10/09
// Last Edited:	2012/10/30
// Description:	Hello Tile Map demo
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

// SGE
#include <SGE.h>
using namespace SGE;

//Daniel Schenker
#include "Frontend.h"
#include "Gameplay.h"
#include "GameContext.h"
#include "GameStates.h"

//=================================================================================================
// Globals
//=================================================================================================

BaseState* gCurrentState = NULL;
GameState::Type gNextState = GameState::Invalid;

GameContext gGameContext;

bool gQuit = false;

//=================================================================================================
// Helper Functions
//=================================================================================================

//=================================================================================================
// SGE Functions
//=================================================================================================

void SGE_Initialize()
{
	gCurrentState = new Gameplay(gGameContext);
	gCurrentState->Load();
}

//-------------------------------------------------------------------------------------------------

void SGE_Terminate()
{
	gCurrentState->Unload();
	delete gCurrentState;
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
		case GameState::Gameplay:
			gCurrentState = new Gameplay(gGameContext);
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
	return gQuit;
}

//-------------------------------------------------------------------------------------------------

void SGE_Render()
{
	gCurrentState->Render();
}

//-------------------------------------------------------------------------------------------------
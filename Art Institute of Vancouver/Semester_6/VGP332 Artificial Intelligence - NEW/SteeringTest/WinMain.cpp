//=================================================================================================
// File:		WinMain.cpp
// Created By:	Daniel Schenker
// Created:		2012/10/01
// Last Edited:	2012/11/05
// Description:	Main entry point of application.
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

// SGE
#include <SGE.h>
using namespace SGE;

// Daniel Schenker
#include "Character.h"

//=================================================================================================
// Globals
//=================================================================================================

Character gCharacter(1);
SGE_Cursor gCursor;

//=================================================================================================
// Class Definitions
//=================================================================================================

void SGE_Initialize()
{
	gCharacter.Load();
	gCharacter.SetPosition(SVector2(400.0f, 300.0f));

	gCursor.Load("target.png");
}

//-------------------------------------------------------------------------------------------------

void SGE_Terminate()
{
	gCharacter.Unload();

	gCursor.Unload();
}

//-------------------------------------------------------------------------------------------------

bool SGE_Update(float deltaTime)
{
	gCursor.Update(deltaTime);

	if(Input_IsKeyPressed(Keys::F1))
	{
		gCharacter.ActivateSeek(true);
		gCharacter.ActivateWander(false);
	}
	else if(Input_IsKeyPressed(Keys::F2))
	{
		gCharacter.ActivateSeek(false);
		gCharacter.ActivateWander(true);
	}

	const float mouseX = static_cast<float>(Input_GetMouseScreenX());
	const float mouseY = static_cast<float>(Input_GetMouseScreenY());
	gCharacter.SetTarget(SVector2((float)mouseX, (float)mouseY));
	gCharacter.Update(deltaTime);

	return Input_IsKeyPressed(SGE::Keys::ESCAPE);
}

//-------------------------------------------------------------------------------------------------

void SGE_Render()
{
	gCharacter.Render();

	gCursor.Render();
}
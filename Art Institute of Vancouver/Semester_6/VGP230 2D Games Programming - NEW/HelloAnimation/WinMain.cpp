//====================================================================================================
// Filename:	WinMain.cpp
// Created by:	Peter Chan
// Description:	Hello Animation demo.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <SGE.h>
using namespace SGE;

#include "Character.h"
#include "Map.h"

//====================================================================================================
// Globals
//====================================================================================================

Character gCharacter;
Map gMap;

SGE_Font gFont;

bool gQuit = false;

//====================================================================================================
// SGE Functions
//====================================================================================================

void SGE_Initialize()
{
	gCharacter.Load();
	gCharacter.SetPosition(SVector2(100.0f, 100.0f));

	gMap.Load("level01.txt", "texturepack01.txt");

	gFont.Load(24);
}

//----------------------------------------------------------------------------------------------------

void SGE_Terminate()
{
	gCharacter.Unload();
	gMap.Unload();
	gFont.Unload();
}

//----------------------------------------------------------------------------------------------------

bool SGE_Update(float fSeconds)
{
	gCharacter.Update(fSeconds, gMap);
	gMap.Update(fSeconds);

	// Are we done?
	if (Input_IsKeyPressed(Keys::ESCAPE))
	{
		gQuit = true;
	}
	return gQuit;
}

//----------------------------------------------------------------------------------------------------

void SGE_Render()
{
	const SVector2 kTarget = gCharacter.GetPosition();
	const int kScreenWidth = IniFile_GetInt("WinWidth", 800);
	const int kScreenHeight = IniFile_GetInt("WinHeight", 600);
	const int kMapWidth = gMap.GetWidth();
	const int kMapHeight = gMap.GetHeight();

	SVector2 offset;
	offset.x = (kScreenWidth * 0.5f) - kTarget.x;
	offset.x = Clamp(offset.x, (float)kScreenWidth - kMapWidth, 0.0f);
	offset.y = (kScreenHeight * 0.5f) - kTarget.y;
	offset.y = Clamp(offset.y, (float)kScreenHeight - kMapHeight, 0.0f);

	gMap.Render(offset);
	gCharacter.Render(offset);

	gFont.Print(gCharacter.GetCurrentState(), 0, 30);
}

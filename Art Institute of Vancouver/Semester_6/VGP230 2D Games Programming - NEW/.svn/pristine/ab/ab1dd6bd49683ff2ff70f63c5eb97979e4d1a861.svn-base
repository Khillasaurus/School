//=================================================================================================
// Filename:	WinMain.cpp
// Created by:	Daniel Schenker
// Description:	Hello SGE demo
//=================================================================================================

//=================================================================================================
// Include
//=================================================================================================

#include <SGE.h>
using namespace SGE;

//=================================================================================================
// Globals
//=================================================================================================

bool gQuit = false;

//!!!Test!!!
SGE_Sprite gSprite;
SVector2 gPosition;

//=================================================================================================
// SGE Functions
//=================================================================================================

void SGE_Initialize()
{
	//!!!Test!!!
	gSprite.Load("LloydIrving.jpg");
}

//-------------------------------------------------------------------------------------------------

void SGE_Terminate()
{
	//!!!Test!!!
	gSprite.Unload();
}

//-------------------------------------------------------------------------------------------------

bool SGE_Update(float deltaTime)
{
	//!!!Test!!!
	//Movement
	const float kSpeed = 100.0f;
	if(Input_IsKeyDown(Keys::RIGHT))
	{
		gPosition.x += kSpeed * deltaTime;
	}
	else if(Input_IsKeyDown(Keys::LEFT))
	{
		gPosition.x -= kSpeed * deltaTime;
	}
	if(Input_IsKeyDown(Keys::UP))
	{
		gPosition.y -= kSpeed * deltaTime;
	}
	else if(Input_IsKeyDown(Keys::DOWN))
	{
		gPosition.y += kSpeed * deltaTime;
	}

	//Quit the application
	if(Input_IsKeyPressed(Keys::ESCAPE))
	{
		gQuit = true;
	}

	return gQuit;
}

//-------------------------------------------------------------------------------------------------

void SGE_Render()
{
	//!!!Test!!!
	gSprite.SetPosition(gPosition);//rendering position, NOT bounding box position
	gSprite.Render();
}

//-------------------------------------------------------------------------------------------------
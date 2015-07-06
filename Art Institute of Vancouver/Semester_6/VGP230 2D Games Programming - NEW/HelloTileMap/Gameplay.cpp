//=================================================================================================
// Filename:	Gameplay.cpp
// Copyright:	Daniel Schenker
// Created:		2012/10/23
// Last Edited:	2012/10/30
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

#include "Gameplay.h"
#include "GameStates.h"

//=================================================================================================
// Class Definitions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------------------------------

Gameplay::Gameplay(GameContext& gc)
: BaseState(gc)
{
}

//-------------------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------------------

Gameplay::~Gameplay()
{
}

//-------------------------------------------------------------------------------------------------
// Implements BaseState
//-------------------------------------------------------------------------------------------------

void Gameplay::Load()
{
	mCharacter.Load();
	mCharacter.SetPosition(SVector2(100.0f, 100.0f));

	/*
	if(mGameContext.GetLevel() == 0)
	{
		mMap.Load("level01.txt", "texturepack01.txt");
	}
	else
	{
		mMap.Load("level02.txt", "texturepack02.txt");
	}
	*/
	mMap.Load("level03.txt", "texturepack03.txt");
}

//-------------------------------------------------------------------------------------------------

void Gameplay::Unload()
{
	mCharacter.Unload();

	mMap.Unload();
}

//-------------------------------------------------------------------------------------------------

int Gameplay::Update(float deltaTime)
{
	mCharacter.Update(deltaTime, mMap);

	GameState::Type nextState = GameState::Invalid;
	if(Input_IsKeyPressed(Keys::ESCAPE))
	{
		nextState = GameState::Frontend;
	}
	return nextState;
}

//-------------------------------------------------------------------------------------------------

void Gameplay::Render()
{
	const SVector2 kTarget = mCharacter.GetPosition();
	const int kScreenWidth = IniFile_GetInt("WinWidth", 800);
	const int kScreenHeight = IniFile_GetInt("WinHeight", 600);
	const int kMapWidth = mMap.GetWidth();
	const int kMapHeight = mMap.GetHeight();

	SVector2 offset;
	offset.x = (kScreenWidth * 0.5f) - kTarget.x;
	offset.x = Clamp(offset.x, static_cast<float>(kScreenWidth - kMapWidth), 0.0f);
	offset.y = (kScreenHeight * 0.5f) - kTarget.y;
	offset.y = Clamp(offset.y, static_cast<float>(kScreenHeight - kMapHeight), 0.0f);

	mMap.Render(offset);
	mCharacter.Render(offset);
}

//-------------------------------------------------------------------------------------------------
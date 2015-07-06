//=================================================================================================
// Filename:	Character.cpp
// Copyright:	Daniel Schenker
// Created:		2012/10/30
// Last Edited:	2012/11/03
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "Character.h"

//=================================================================================================
// Class Definitions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------------------------------

Character::Character()
: mPosition(0.0f, 0.0f)
, mVelocity(0.0f, 0.0f)
{
	// Empty
}

//-------------------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------------------

Character::~Character()
{
}

//-------------------------------------------------------------------------------------------------
// SGE specific
//-------------------------------------------------------------------------------------------------

void Character::Load()
{
	mSprite.Load("PeterChan/fighter_2.png");
}

//-------------------------------------------------------------------------------------------------

void Character::Unload()
{
	mSprite.Unload();
}

//-------------------------------------------------------------------------------------------------

void Character::Update(float deltaTime)
{
	const float kSpeed = 500.0f;

	// Check horizontal movement
	if(Input_IsKeyDown(Keys::RIGHT))
	{
		mVelocity.x = kSpeed * deltaTime;
	}
	else if(Input_IsKeyDown(Keys::LEFT))
	{
		mVelocity.x = -kSpeed * deltaTime;
	}
	else
	{
		mVelocity.x = 0.0f;
	}

	// Check vertical movement
	if(Input_IsKeyDown(Keys::DOWN))
	{
		mVelocity.y = kSpeed * deltaTime;
	}
	else if(Input_IsKeyDown(Keys::UP))
	{
		mVelocity.y = -kSpeed * deltaTime;
	}
	else
	{
		mVelocity.y = 0.0f;
	}

	mPosition += mVelocity;
}

//-------------------------------------------------------------------------------------------------

void Character::Render(const SVector2& offset)
{
	const int kTextureWidth = mSprite.GetWidth();
	const int kTextureHeight = mSprite.GetHeight();
	const SVector2 pos(mPosition.x - (kTextureWidth * 0.5f), mPosition.y - kTextureHeight);
	mSprite.SetPosition(pos + offset);
	mSprite.Render();
}
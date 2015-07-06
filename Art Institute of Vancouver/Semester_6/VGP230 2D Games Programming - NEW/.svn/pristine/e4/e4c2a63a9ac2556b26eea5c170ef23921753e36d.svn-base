//=================================================================================================
// Filename:	Character.cpp
// Copyright:	Daniel Schenker
// Created:		2012/10/30
// Last Edited:	2012/10/31
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
: mMass(0.0f)
, mPosition(0.0f, 0.0f)
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
	mSprite.Load("fighter_2.png");
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
	SVector2 displacement(0.0f, 0.0f);

	// Check horizontal movement
	if(Input_IsKeyDown(Keys::RIGHT))
	{
		displacement.x = kSpeed * deltaTime;
	}
	else if(Input_IsKeyDown(Keys::LEFT))
	{
		displacement.x = -kSpeed * deltaTime;
	}
	else
	{
		displacement.x = 0.0f;
	}

	// Check vertical movement
	if(Input_IsKeyDown(Keys::DOWN))
	{
		displacement.y = kSpeed * deltaTime;
	}
	else if(Input_IsKeyDown(Keys::UP))
	{
		displacement.y = -kSpeed * deltaTime;
	}
	else
	{
		displacement.y = 0.0f;
	}

	mPosition += displacement;
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

//-------------------------------------------------------------------------------------------------
// Mutators
//-------------------------------------------------------------------------------------------------

void Character::SetMass(float mass)
{
	if(mass >= 0.0f)
	{
		mMass = mass;
	}
}
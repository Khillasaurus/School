//=================================================================================================
// Filename:	Character.cpp
// Copyright:	Daniel Schenker
// Created:		2012/10/30
// Last Edited:	2012/10/30
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
, mJumping(true)
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
	mSprite.Load("mario_idle_01.png");
}

//-------------------------------------------------------------------------------------------------

void Character::Unload()
{
	mSprite.Unload();
}

//-------------------------------------------------------------------------------------------------

void Character::Update(float deltaTime, const Map& map)
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

	// Check collision
	SRect bb = GetBoundingBox();
	SRect newbb = bb + SVector2(mVelocity.x, 0.0f);
	SRect rightbb = map.GetBoudingBoxFromSegment(newbb.GetRightSegment());
	SRect leftbb = map.GetBoudingBoxFromSegment(newbb.GetLeftSegment());
	
	// Right Collision
	if(mVelocity.x > 0.0f && rightbb.IsValid())
	{
		mPosition.x += static_cast<int>(rightbb.min.x - bb.max.x) - 1.0f;
	}
	// Left Collision
	else if(mVelocity.x < 0.0f && leftbb.IsValid())
	{
		mPosition.x += static_cast<int>(leftbb.max.x - bb.min.x) + 1.0f;
	}
	else
	{
		mPosition.x += static_cast<int>(mVelocity.x);
	}

	// Check vertical movement
	/*if(Input_IsKeyDown(Keys::DOWN))
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
	}*/
	if(Input_IsKeyPressed(Keys::UP) && !mJumping)
	{
		mVelocity.y = -30.0f;
		mJumping = true;
	}
	else
	{
		mVelocity.y += 100.0f * deltaTime;
	}

	// Check collision
	newbb = bb + SVector2(0.0f, mVelocity.y);
	SRect topbb = map.GetBoudingBoxFromSegment(newbb.GetTopSegment());
	SRect bottombb = map.GetBoudingBoxFromSegment(newbb.GetBottomSegment());
	
	// Top Collision
	if(mVelocity.y < 0.0f && topbb.IsValid())
	{
		mPosition.y += static_cast<int>(topbb.max.y - bb.min.y) + 1.0f;
		//Note: gravity specific
		mVelocity.y = 0.0f;
	}
	// Bottom Collision
	else if(mVelocity.y > 0.0f && bottombb.IsValid())
	{
		mPosition.y += static_cast<int>(bottombb.min.y - bb.max.y) - 1.0f;
		//Note: gravity specific
		mVelocity.y = 0.0f;
		mJumping = false;
	}
	else
	{
		mPosition.y += static_cast<int>(mVelocity.y);
	}
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

SRect Character::GetBoundingBox() const
{
	return SRect
	(
		mPosition.x - 16.0f,
		mPosition.y - 56.0f,
		mPosition.x + 16.0f,
		mPosition.y
	);
}
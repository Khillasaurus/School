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
	mSprite.Load("player.png");
}

//-------------------------------------------------------------------------------------------------

void Character::Unload()
{
	mSprite.Unload();
}

//-------------------------------------------------------------------------------------------------

void Character::Update(float deltaTime, const Map& map, const SVector2& renderOffset)
{
	const float kSpeed = 256.0f;

	// Check horizontal movement
	if(Input_IsKeyDown(Keys::RIGHT))
	{
		mVelocity.x = kSpeed * deltaTime;
		mSprite.SetRotation(1.575f);
	}
	else if(Input_IsKeyDown(Keys::LEFT))
	{
		mVelocity.x = -kSpeed * deltaTime;
		mSprite.SetRotation(-1.575f);
	}
	else
	{
		mVelocity.x = 0.0f;
	}

	// Check collision
	SRect bb = GetBoundingBox(renderOffset);
	SRect newbb = bb + SVector2(mVelocity.x, 0.0f);

	SLineSegment tempRightLS(newbb.GetRightSegment().from.x - renderOffset.x,
							newbb.GetRightSegment().from.y - renderOffset.y,
							newbb.GetRightSegment().to.x - renderOffset.x,
							newbb.GetRightSegment().to.y - renderOffset.y);
	SLineSegment tempLeftLS(newbb.GetLeftSegment().from.x - renderOffset.x,
							newbb.GetLeftSegment().from.y - renderOffset.y,
							newbb.GetLeftSegment().to.x - renderOffset.x,
							newbb.GetLeftSegment().to.y - renderOffset.y);

	SRect rightbb = map.GetBoudingBoxFromSegment(tempRightLS);
	SRect leftbb = map.GetBoudingBoxFromSegment(tempLeftLS);

	Graphics_DebugRect(bb, 0xF04BC3);
	Graphics_DebugRect(newbb, 0x004BC3);
	Graphics_DebugRect(rightbb, 0xF04B00);
	Graphics_DebugRect(leftbb, 0xF000C3);
	
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
	if(Input_IsKeyDown(Keys::DOWN))
	{
		mVelocity.y = kSpeed * deltaTime;
		mSprite.SetRotation(3.15f);
	}
	else if(Input_IsKeyDown(Keys::UP))
	{
		mVelocity.y = -kSpeed * deltaTime;
		mSprite.SetRotation(0.0f);
	}
	else
	{
		mVelocity.y = 0.0f;
	}

	// Check collision
	newbb = bb + SVector2(0.0f, mVelocity.y);
	SRect topbb = map.GetBoudingBoxFromSegment(newbb.GetTopSegment());
	SRect bottombb = map.GetBoudingBoxFromSegment(newbb.GetBottomSegment());
	
	// Top Collision
	if(mVelocity.y < 0.0f && topbb.IsValid())
	{
		mPosition.y += static_cast<int>(topbb.max.y - bb.min.y) + 1.0f;
	}
	// Bottom Collision
	else if(mVelocity.y > 0.0f && bottombb.IsValid())
	{
		mPosition.y += static_cast<int>(bottombb.min.y - bb.max.y) - 1.0f;
	}
	else
	{
		mPosition.y += static_cast<int>(mVelocity.y);
	}

	mPosition += mVelocity;
}

//-------------------------------------------------------------------------------------------------

void Character::Render(const SVector2& renderOffset)
{
	const int kTextureWidth = mSprite.GetWidth();
	const int kTextureHeight = mSprite.GetHeight();
	const SVector2 pos(mPosition.x - (kTextureWidth * 0.5f), mPosition.y - (kTextureHeight * 0.5f));
	mSprite.SetPosition(pos + renderOffset);
	mSprite.Render();
}

//-------------------------------------------------------------------------------------------------

SRect Character::GetBoundingBox(const SVector2& renderOffset) const
{
	return SRect
	(
		mPosition.x - 16.0f + renderOffset.x,
		mPosition.y - 16.0f + renderOffset.y,
		mPosition.x + 16.0f + renderOffset.x,
		mPosition.y + 16.0f + renderOffset.y
	);
}
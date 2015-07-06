//====================================================================================================
// Filename:	CharacterFall.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterFall.h"

#include "Character.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CharacterFall::CharacterFall(Character* pOwner)
	: CharacterState(pOwner, "Fall")
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CharacterFall::~CharacterFall()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void CharacterFall::Load()
{
	mSprite.Add("mario_fall_01.png");
}

//----------------------------------------------------------------------------------------------------

void CharacterFall::Unload()
{
	mSprite.Unload();
}

//----------------------------------------------------------------------------------------------------

void CharacterFall::Update(float fSeconds)
{
	// Update sprite
	mSprite.Update(fSeconds);

	// Update physics
	const float kSpeed = 500.0f;
	SVector2 vel(mpOwner->GetVelocity());
	if (Input_IsKeyDown(Keys::RIGHT))
	{
		vel.x = kSpeed * fSeconds;
		mpOwner->SetFacingLeft(false);
	}
	else if (Input_IsKeyDown(Keys::LEFT))
	{
		vel.x = -kSpeed * fSeconds;
		mpOwner->SetFacingLeft(true);
	}
	else
	{
		vel.x = 0.0f;
	}
	mpOwner->SetVelocity(vel);
}

//----------------------------------------------------------------------------------------------------

void CharacterFall::Render(const SVector2& offset)
{
	const int kTextureWidth = mSprite.GetWidth();
	const int kTextureHeight = mSprite.GetHeight();
	const SVector2 ownerPos(mpOwner->GetPosition());
	const SVector2 renderPos(ownerPos.x - (kTextureWidth * 0.5f), ownerPos.y - kTextureHeight);
	bool facingLeft = mpOwner->IsFacingLeft();
	mSprite.SetPosition(renderPos + offset);
	mSprite.SetFlipH(facingLeft);
	mSprite.Render();
}

//----------------------------------------------------------------------------------------------------

void CharacterFall::Enter()
{
	mSprite.Play(1.0f, true);
}

//----------------------------------------------------------------------------------------------------

void CharacterFall::Exit()
{
	mSprite.Stop();
	mSprite.Reset();
}

//----------------------------------------------------------------------------------------------------

SRect CharacterFall::GetBoundingBox() const
{
	const SVector2 pos(mpOwner->GetPosition());
	return SRect
	(
		pos.x - 16.0f,
		pos.y - 56.0f,
		pos.x + 16.0f,
		pos.y
	);
}
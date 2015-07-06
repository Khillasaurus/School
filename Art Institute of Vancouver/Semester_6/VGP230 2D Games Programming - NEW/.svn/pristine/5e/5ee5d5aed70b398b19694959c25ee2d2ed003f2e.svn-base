//====================================================================================================
// Filename:	CharacterJump.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterJump.h"

#include "Character.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CharacterJump::CharacterJump(Character* pOwner)
	: CharacterState(pOwner, "Jump")
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CharacterJump::~CharacterJump()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void CharacterJump::Load()
{
	mSprite.Add("mario_jump_01.png");
}

//----------------------------------------------------------------------------------------------------

void CharacterJump::Unload()
{
	mSprite.Unload();
}

//----------------------------------------------------------------------------------------------------

void CharacterJump::Update(float fSeconds)
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

	// State transitions
	if (vel.y >= 0.0f)
	{
		mpOwner->ChangeState(AS_Fall);
	}
}

//----------------------------------------------------------------------------------------------------

void CharacterJump::Render(const SVector2& offset)
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

void CharacterJump::Enter()
{
	mSprite.Play(1.0f, true);
	SVector2 vel(mpOwner->GetVelocity());
	vel.y = -25.0f;
	mpOwner->SetVelocity(vel);
}

//----------------------------------------------------------------------------------------------------

void CharacterJump::Exit()
{
	mSprite.Stop();
	mSprite.Reset();
}

//----------------------------------------------------------------------------------------------------

SRect CharacterJump::GetBoundingBox() const
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
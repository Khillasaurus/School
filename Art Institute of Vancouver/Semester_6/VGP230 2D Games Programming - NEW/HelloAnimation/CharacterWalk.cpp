//====================================================================================================
// Filename:	CharacterWalk.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterWalk.h"

#include "Character.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CharacterWalk::CharacterWalk(Character* pOwner)
	: CharacterState(pOwner, "Walk")
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CharacterWalk::~CharacterWalk()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk::Load()
{
	mSprite.Add("mario_walk_01.png");
	mSprite.Add("mario_walk_02.png");
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk::Unload()
{
	mSprite.Unload();
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk::Update(float fSeconds)
{
	// Update sprite
	mSprite.Update(fSeconds);

	// State transitions
	const float kSpeed = 500.0f;
	if (Input_IsKeyPressed(Keys::UP))
	{
		mpOwner->ChangeState(AS_Jump);
	}
	else if (Input_IsKeyDown(Keys::RIGHT))
	{
		SVector2 vel(kSpeed * fSeconds, 0.0f);
		mpOwner->SetVelocity(vel);
		mpOwner->SetFacingLeft(false);
	}
	else if (Input_IsKeyDown(Keys::LEFT))
	{
		SVector2 vel(-kSpeed * fSeconds, 0.0f);
		mpOwner->SetVelocity(vel);
		mpOwner->SetFacingLeft(true);
	}
	else
	{
		mpOwner->SetVelocity(SVector2());
		mpOwner->ChangeState(AS_Idle);
	}
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk::Render(const SVector2& offset)
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

void CharacterWalk::Enter()
{
	mSprite.Play(8.0f, true);
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk::Exit()
{
	mSprite.Stop();
	mSprite.Reset();
}

//----------------------------------------------------------------------------------------------------

SRect CharacterWalk::GetBoundingBox() const
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
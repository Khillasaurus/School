//====================================================================================================
// Filename:	CharacterIdle.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterIdle.h"

#include "Character.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CharacterIdle::CharacterIdle(Character* pOwner)
	: CharacterState(pOwner, "Idle")
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CharacterIdle::~CharacterIdle()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle::Load()
{
	mSprite.Add("mario_idle_01.png");
	mSprite.Add("mario_idle_01.png");
	mSprite.Add("mario_idle_01.png");
	mSprite.Add("mario_idle_02.png");
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle::Unload()
{
	mSprite.Unload();
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle::Update(float fSeconds)
{
	// Update sprite
	mSprite.Update(fSeconds);

	// State transitions
	if (Input_IsKeyPressed(Keys::UP))
	{
		mpOwner->ChangeState(AS_Jump);
	}
	else if (Input_IsKeyDown(Keys::RIGHT) || Input_IsKeyDown(Keys::LEFT))
	{
		mpOwner->ChangeState(AS_Walk);
	}
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle::Render(const SVector2& offset)
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

void CharacterIdle::Enter()
{
	mSprite.Play(4.0f, true);
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle::Exit()
{
	mSprite.Stop();
	mSprite.Reset();
}

//----------------------------------------------------------------------------------------------------

SRect CharacterIdle::GetBoundingBox() const
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
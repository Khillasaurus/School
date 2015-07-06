//====================================================================================================
// Filename:	Character.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Character.h"

#include "CharacterFall.h"
#include "CharacterIdle.h"
#include "CharacterJump.h"
#include "CharacterWalk.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

Character::Character()
	: mpCurrentState(NULL)
	, mPosition(0.0f, 0.0f)
	, mVelocity(0.0f, 0.0f)
	, mFacingLeft(false)
{
	memset(mCharacterStates, 0, sizeof(CharacterState*) * AS_Max);
}

//----------------------------------------------------------------------------------------------------

Character::~Character()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void Character::Load()
{
	// Clear everything
	Unload();

	// Create character states
	mCharacterStates[AS_Idle] = new CharacterIdle(this);
	mCharacterStates[AS_Walk] = new CharacterWalk(this);
	mCharacterStates[AS_Jump] = new CharacterJump(this);
	mCharacterStates[AS_Fall] = new CharacterFall(this);

	// Load state resources
	for (int i = 0; i < AS_Max; ++i)
	{
		mCharacterStates[i]->Load();
	}

	// Set default state
	ChangeState(AS_Fall);
}

//----------------------------------------------------------------------------------------------------

void Character::Unload()
{
	for (int i = 0; i < AS_Max; ++i)
	{
		if (mCharacterStates[i] != NULL)
		{
			mCharacterStates[i]->Unload();
			delete mCharacterStates[i];
			mCharacterStates[i] = NULL;
		}
	}
	mpCurrentState = NULL;
}

//----------------------------------------------------------------------------------------------------

void Character::Update(float fSeconds, const Map& map)
{
	// Update the current state
	mpCurrentState->Update(fSeconds);

	// Apply gravity
	mVelocity.y += 100.0f * fSeconds;

	// Apply movement
	CheckCollision(fSeconds, map);
}

//----------------------------------------------------------------------------------------------------

void Character::Render(const SVector2& offset)
{
	mpCurrentState->Render(offset);
}

//----------------------------------------------------------------------------------------------------

void Character::ChangeState(AnimationState as)
{
	// Check if we are already in this state
	if (mpCurrentState == mCharacterStates[as])
	{
		return;
	}

	// Exit the current state
	if (mpCurrentState != NULL)
	{
		mpCurrentState->Exit();
	}

	// Switch to the new state
	mpCurrentState = mCharacterStates[as];

	// Enter the new state
	if (mpCurrentState != NULL)
	{
		mpCurrentState->Enter();
	}
}

//----------------------------------------------------------------------------------------------------

const char* Character::GetCurrentState()
{
	const char* name = "Unknown";
	if (mpCurrentState != NULL)
	{
		name = mpCurrentState->GetName();
	}
	return name;
}

//----------------------------------------------------------------------------------------------------

SRect Character::GetBoundingBox() const
{
	return mpCurrentState->GetBoundingBox();
}

//----------------------------------------------------------------------------------------------------

void Character::CheckCollision(float fSeconds, const Map& map)
{
	// Check collision
	SRect bb = GetBoundingBox();
	SRect newbb = bb + SVector2(mVelocity.x, 0.0f);
	SRect rightbb = map.GetBoundingBoxFromSegment(newbb.GetRightSegment());
	SRect leftbb = map.GetBoundingBoxFromSegment(newbb.GetLeftSegment());

	// Right collision
	if (mVelocity.x > 0.0f && rightbb.IsValid())
	{
		mPosition.x += static_cast<int>(rightbb.min.x - bb.max.x) - 1.0f;
	}
	// Left collision
	else if (mVelocity.x < 0.0f && leftbb.IsValid())
	{
		mPosition.x += static_cast<int>(leftbb.max.x - bb.min.x) + 1.0f;
	}
	else
	{
		mPosition.x += static_cast<int>(mVelocity.x);
	}

	// Check collision
	newbb = bb + SVector2(0.0f, mVelocity.y);
	SRect bottombb = map.GetBoundingBoxFromSegment(newbb.GetBottomSegment());
	SRect topbb = map.GetBoundingBoxFromSegment(newbb.GetTopSegment());

	// Bottom collision
	if (mVelocity.y > 0.0f && bottombb.IsValid())
	{
		mPosition.y += static_cast<int>(bottombb.min.y - bb.max.y) - 1.0f;
		mVelocity.y = 0.0f;
		if (mpCurrentState == mCharacterStates[AS_Fall])
		{
			ChangeState(AS_Idle);
		}
	}
	// Top collision
	else if (mVelocity.y < 0.0f && topbb.IsValid())
	{
		mPosition.y += static_cast<int>(topbb.max.y - bb.min.y) + 1.0f;
		mVelocity.y = 0.0f;
	}
	else
	{
		mPosition.y += static_cast<int>(mVelocity.y);
		if (mpCurrentState == mCharacterStates[AS_Idle] ||
			mpCurrentState == mCharacterStates[AS_Walk])
		{
			ChangeState(AS_Fall);
		}
	}
}
//=================================================================================================
// File:		SeekBehavior.cpp
// Created:		2012/10/29
// Last Edited:	2012/10/29
// Copyright:	Daniel Schenker
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

// Daniel Schenker
#include "Agent.h"
#include "SeekBehavior.h"

//=================================================================================================
// Class Defintions
//=================================================================================================

SeekBehavior::SeekBehavior(Agent* pOwner, float weight)
: SteeringBehavior(pOwner, weight)
{
	// Empty
}

//-------------------------------------------------------------------------------------------------

SeekBehavior::~SeekBehavior()
{
	// Empty
}

//-------------------------------------------------------------------------------------------------

SVector2 SeekBehavior::Update(float deltaTime)
{
	SVector2 agentToTarget = mpOwner->GetTarget() - mpOwner->GetPosition();
	mDesiredVelocity = Normalize(agentToTarget) * mpOwner->GetMaxSpeed();
	mSeekVelocity = mDesiredVelocity - mpOwner->GetVelocity();
	return mSeekVelocity;
};

//-------------------------------------------------------------------------------------------------

void SeekBehavior::Render()
{
	const SVector2 pos = mpOwner->GetPosition();
	const SVector2 vel = mpOwner->GetVelocity();
	Graphics_DebugLine(pos, pos + vel, 0x0000FF);
	Graphics_DebugLine(pos, pos + mDesiredVelocity, 0x00FF00);
	Graphics_DebugLine(pos, pos + mSeekVelocity, 0xFF00FF);
};
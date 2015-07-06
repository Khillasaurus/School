//=================================================================================================
// File:		ArriveBehavior.cpp
// Created By:	Daniel Schenker
// Created:		2012/11/05
// Last Edited:	2012/11/05
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

// Daniel Schenker
#include "Agent.h"
#include "ArriveBehavior.h"

//=================================================================================================
// Class Defintions
//=================================================================================================

ArriveBehavior::ArriveBehavior(Agent* pOwner, float weight)
: SteeringBehavior(pOwner, weight)
, mDesiredVelocity(0.0f, 0.0f)
, mArriveVelocity(0.0f, 0.0f)
, mBrakeDistance(0.0f)
{
	// Empty
}

//-------------------------------------------------------------------------------------------------

SVector2 ArriveBehavior::Update(float deltaTime)
{
	SVector2 agentToTarget = mpOwner->GetTarget() - mpOwner->GetPosition();
	float distance = agentToTarget.Length();

	if(distance > mBrakeDistance)
	{
		mDesiredVelocity = agentToTarget / distance * mpOwner->GetMaxSpeed();
	}
	else
	{
		// If target is close, slow down
		mDesiredVelocity = agentToTarget / distance/* * acceleration*/;
	}
	mArriveVelocity = mDesiredVelocity - mpOwner->GetVelocity();
	return mArriveVelocity;
};

//-------------------------------------------------------------------------------------------------

void ArriveBehavior::Render()
{
	const SVector2 pos = mpOwner->GetPosition();
	const SVector2 vel = mpOwner->GetVelocity();
	Graphics_DebugLine(pos, pos + vel, 0x0000FF);
	Graphics_DebugLine(pos, pos + mDesiredVelocity, 0x00FF00);
	Graphics_DebugLine(pos, pos + mArriveVelocity, 0xFF00FF);
};
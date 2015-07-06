//=================================================================================================
// File:		WanderBehavior.cpp
// Created By:	Daniel Schenker
// Created:		2012/11/05
// Last Edited:	2012/11/05
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

// Daniel Schenker
#include "Agent.h"
#include "WanderBehavior.h"

//=================================================================================================
// Class Definitions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructors
//-------------------------------------------------------------------------------------------------

WanderBehavior::WanderBehavior(Agent* pOwner, float weight)
: SteeringBehavior(pOwner, weight)
, mLocalTarget(0.0f, 1.0f)
, mWanderRadius(0.0f)
, mWanderDistance(1.0f)
, mWanderJitter(0.0f)
{
	// Empty
}

//-------------------------------------------------------------------------------------------------
// Implements SteeringBehavior
//-------------------------------------------------------------------------------------------------

SVector2 WanderBehavior::Update(float deltaTime)
{
	// Update local target
	const SVector2 minJitter(-mWanderJitter, -mWanderJitter);
	const SVector2 maxJitter(mWanderJitter, mWanderJitter);
	mLocalTarget += RandomVector2(minJitter, maxJitter);
	mLocalTarget.Normalize();
	mLocalTarget *= mWanderRadius;

	// Compute actual target
	SVector2 target = mLocalTarget + SVector2(0.0f, mWanderDistance);
	SMatrix33 transform = mpOwner->GetTransform();
	target = transform.TransformCoord(target);

	SVector2 agentToTarget = target - mpOwner->GetPosition();
	SVector2 desiredVelocity = Normalize(agentToTarget) * mpOwner->GetMaxSpeed();
	return desiredVelocity - mpOwner->GetVelocity();
}

//-------------------------------------------------------------------------------------------------

void WanderBehavior::Render()
{
	SMatrix33 transform = mpOwner->GetTransform();
	
	SVector2 center = SVector2(0.0f, mWanderDistance);
	SVector2 target = mLocalTarget + center;
	center = transform.TransformCoord(center);
	target = transform.TransformCoord(target);

	Graphics_DebugCircle(center, mWanderRadius, 0x00FF00);
	Graphics_DebugCircle(target, 2.0f, 0xFF0000);
	Graphics_DebugLine(mpOwner->GetPosition(), target, 0x0000FF);
}
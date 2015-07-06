#ifndef INCLUDED_AI_WANDERBEHAVIOR_H
#define INCLUDED_AI_WANDERBEHAVIOR_H

//=================================================================================================
// File:		WanderBehavior.h
// Created:		2012/11/05
// Last Edited:	2012/11/05
// Created By:	Daniel Schenker
// Description	WanderBehavior.h
//=================================================================================================

//=================================================================================================
// Forward Declarations
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

#include "SteeringBehavior.h"

//=================================================================================================
// Class Declarations
//=================================================================================================

class WanderBehavior : public SteeringBehavior
{
public:
	WanderBehavior(Agent* pOwner, float weight);

	// Implements SteeringBehavior
	virtual SVector2 Update(float deltaTime);
	virtual void Render();

	// Accessors
	float GetWanderRadius() const			{ return  mWanderRadius; }
	float GetWanderDistance() const			{ return  mWanderDistance; }
	float GetWanderJitter() const			{ return mWanderJitter; }

	// Mutators
	void SetWanderRadius(float radius)		{ mWanderRadius = radius; }
	void SetWanderDistance(float dist)		{ mWanderDistance = dist; }
	void SetWanderJitter(float jitter)		{ mWanderJitter = jitter; }

private:
	SVector2 mLocalTarget;
	float mWanderRadius;
	float mWanderDistance;
	float mWanderJitter;
};

#endif //#ifndef INCLUDED_AI_WANDERBEHAVIOR_H
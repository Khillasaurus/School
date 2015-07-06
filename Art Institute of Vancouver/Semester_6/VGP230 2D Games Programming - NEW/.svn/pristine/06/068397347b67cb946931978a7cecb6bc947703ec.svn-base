#ifndef INCLUDED_AI_ARRIVEBEHAVIOR_H
#define INCLUDED_AI_ARRIVEBEHAVIOR_H

//=================================================================================================
// File:		ArriveBehavior.h
// Created By:	Daniel Schenker
// Created:		2012/11/05
// Last Edited:	2012/11/05
// Description	ArriveBehavior.h
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

#include "SteeringBehavior.h"

//=================================================================================================
// Class Declarations
//=================================================================================================

class ArriveBehavior : public SteeringBehavior
{
public:
	ArriveBehavior(Agent* pOwner, float weight);

	// Implements SteeringBehaviour
	virtual SVector2 Update(float deltaTime);
	virtual void Render();

	// Accesors
	float GetBrakeDistance() const			{ return mBrakeDistance; }

	// Mutators
	void SetBrakeDistance(float dist)		{ mBrakeDistance = dist; }

private:
	SVector2 mDesiredVelocity;
	SVector2 mArriveVelocity;
	float mBrakeDistance;
};

#endif //#ifndef INCLUDED_AI_ARRIVEBEHAVIOR_H
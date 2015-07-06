#ifndef INCLUDED_AI_STEERINGBEHAVIOR_H
#define INCLUDED_AI_STEERINGBEHAVIOR_H

//=================================================================================================
// File:		SteeringBehavior.h
// Created:		2012/10/29
// Last Edited:	2012/10/29
// Copyright:	Daniel Schenker
// Description	SteeringBehavior.h
//=================================================================================================

//=================================================================================================
// Forward Declarations
//=================================================================================================

class Agent;

//=================================================================================================
// Includes
//=================================================================================================

#include <SGE.h>
using namespace SGE;

//=================================================================================================
// Class Declarations
//=================================================================================================

class SteeringBehavior
{
public:
	SteeringBehavior(Agent* pOwner, float weight);
	virtual ~SteeringBehavior();

	virtual SVector2 Update(float deltaTime) = 0;
	virtual void Render() {};

	// Accessosr
	float GetWeight() const			{ return mWeight; }
	bool IsActive() const			{ return mActive; }

	// Mutators
	void SetActive(bool active)		{ mActive = active; }

protected:
	Agent* mpOwner;
	bool mActive;
	float mWeight;
};

#endif //#ifndef INCLUDED_AI_STEERINGBEHAVIOR_H
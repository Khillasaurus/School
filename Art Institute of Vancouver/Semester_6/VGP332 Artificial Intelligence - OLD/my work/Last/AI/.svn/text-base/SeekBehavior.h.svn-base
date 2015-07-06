#ifndef INCLUDED_AI_SEEKBEHAVIOR_H
#define INCLUDED_AI_SEEKBEHAVIOR_H

//=================================================================================================
// File:		SeekBehavior.h
// Created:		2012/10/29
// Last Edited:	2012/10/29
// Copyright:	Daniel Schenker
// Description	SeekBehavior.h
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

#include "SteeringBehavior.h"

//=================================================================================================
// Class Declarations
//=================================================================================================

class SeekBehavior : public SteeringBehavior
{
public:
	SeekBehavior(Agent* pOwner, float weight);
	~SeekBehavior();

	// Implements SteeringBehaviour
	virtual SVector2 Update(float deltaTime);
	virtual void Render();

	SVector2 mDesiredVelocity;
	SVector2 mSeekVelocity;
};

#endif //#ifndef INCLUDED_AI_SEEKBEHAVIOR_H
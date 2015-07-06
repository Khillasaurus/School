//=================================================================================================
// File:		SteeringBehavior.cpp
// Created:		2012/10/29
// Last Edited:	2012/10/29
// Copyright:	Daniel Schenker
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "SteeringBehavior.h"

//=================================================================================================
// Class Declarations
//=================================================================================================

SteeringBehavior::SteeringBehavior(Agent* pOwner, float weight)
: mpOwner(pOwner)
, mActive(false)
, mWeight(weight)
{
	// Empty
}

//-------------------------------------------------------------------------------------------------

SteeringBehavior::~SteeringBehavior()
{
	// Empty
}
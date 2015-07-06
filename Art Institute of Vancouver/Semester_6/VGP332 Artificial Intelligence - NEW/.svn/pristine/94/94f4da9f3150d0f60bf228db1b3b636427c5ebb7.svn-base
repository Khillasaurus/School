#ifndef INCLUDED_STEERINGMODULE_H
#define INCLUDED_STEERINGMODULE_H

//=================================================================================================
// File:		SteeringModule.h
// Created:		2012/10/29
// Last Edited:	2012/10/29
// Copyright:	Daniel Schenker
// Description	SteeringModule.h
//=================================================================================================

//=================================================================================================
// Forward Declarations
//=================================================================================================

//Daniel Schenker
class SteeringBehavior;

//=================================================================================================
// Includes
//=================================================================================================

//STL
#include <list>

//=================================================================================================
// Class Declarations
//=================================================================================================

class SteeringModule
{
public:
	SteeringModule();
	~SteeringModule();

	void AddBehavior(SteeringBehavior* pBehavior);
	void Purge();

	SVector2 Update(float deltaTime);

private:
	std::list<SteeringBehavior*> mBehaviors;
};

#endif //#ifndef INCLUDED_STEERINGMODULE_H
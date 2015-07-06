//=================================================================================================
// File:		SteeringModule.cpp
// Created:		2012/10/29
// Last Edited:	2012/10/29
// Copyright:	Daniel Schenker
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//STL
#include <list>

// Daniel Schenker
#include "SteeringBehavior.h"
#include "SteeringModule.h"

//=================================================================================================
// Class Definitions
//=================================================================================================

SteeringModule::SteeringModule()
{
}

//-------------------------------------------------------------------------------------------------

SteeringModule::~SteeringModule()
{
	Purge();
}

//-------------------------------------------------------------------------------------------------

void SteeringModule::AddBehavior(SteeringBehavior* pBehavior)
{
	mBehaviors.push_back(pBehavior);
}

//-------------------------------------------------------------------------------------------------

void SteeringModule::Purge()
{
	for(std::list<SteeringBehavior*>::iterator iter = mBehaviors.begin();
		iter != mBehaviors.end();
		++iter)
	{
		SteeringBehavior* pBehavior = (*iter);
		delete pBehavior;
	}
	mBehaviors.clear();
}

//-------------------------------------------------------------------------------------------------

SVector2 SteeringModule::Update(float deltaTime)
{
	SVector2 totalForce;
	for(std::list<SteeringBehavior*>::iterator iter = mBehaviors.begin();
		iter != mBehaviors.end();
		++iter)
	{
		SteeringBehavior* pBehavior = (*iter);
		if(pBehavior->IsActive())
		{
			totalForce += pBehavior->Update(deltaTime) * pBehavior->GetWeight();
		}
	}
	return totalForce;
}
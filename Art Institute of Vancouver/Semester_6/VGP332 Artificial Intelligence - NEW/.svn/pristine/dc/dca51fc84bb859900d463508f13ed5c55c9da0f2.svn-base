//=================================================================================================
// File:		Agent.cpp
// Created:		2012/10/29
// Last Edited:	2012/10/29
// Copyright:	Daniel Schenker
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

#include "Agent.h"
#include "World.h"

Agent::Agent(int id, const World& world)
: mWorld(world)
, mPosition(0.0f, 0.0f)
, mVelocity(0.0f, 0.0f)
, mMaxSpeed(500.0f)
, mHeading(0.0f, 1.0f)
, mSide(1.0f, 0.0f)
, mID(id)
{
	// Empty
};

//-------------------------------------------------------------------------------------------------

Agent::~Agent()
{
};

//-------------------------------------------------------------------------------------------------

SMatrix33 Agent::GetTransform() const
{
	SMatrix33 transform;
	transform._11 = mSide.x;
	transform._12 = mSide.y;
	transform._21 = mHeading.x;
	transform._22 = mHeading.y;
	transform._31 = mPosition.x;
	transform._32 = mPosition.y;
	return transform;
}

//-------------------------------------------------------------------------------------------------

void Agent::SetHeading(const SVector2& heading)
{
	mHeading = heading;
	mHeading.Normalize();
	mSide = mHeading;
	mSide.PerpendicularLH();
}
#ifndef INCLUDED_AGENT_H
#define INCLUDED_AGENT_H

//=================================================================================================
// File:		Agent.h
// Created:		2012/10/29
// Last Edited:	2012/10/29
// Copyright:	Daniel Schenker
// Description	Holds agent data.
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

// SGE
#include <SGE.h>
using namespace SGE;

//STL
#include <list>

//=================================================================================================
// Class Declarations
//=================================================================================================

class Agent
{
public:
	Agent(int id);
	virtual ~Agent();

	SMatrix33 GetTransform() const;

	// Accessors
	const SVector2& GetPosition() const			{ return mPosition; }
	const SVector2& GetVelocity() const			{ return mVelocity; }
	float GetMaxSpeed() const					{ return mMaxSpeed; }
	const SVector2& GetTarget() const			{ return mTarget; }
	const SVector2& GetHeading() const			{ return mHeading; }
	const int GetID() const						{ return mID; }

	// Mutators
	void SetPosition(const SVector2& pos)		{ mPosition = pos; }
	void SetVelocity(const SVector2& vel)		{ mVelocity = vel; }
	void SetMaxSpeed(float vel)					{ mMaxSpeed = vel; }
	void SetTarget(const SVector2 target)		{ mTarget = target; }
	void SetHeading(const SVector2& heading);


protected:
	SVector2 mPosition;
	SVector2 mVelocity;
	float mMaxSpeed;
	SVector2 mTarget;
	SVector2 mHeading;
	SVector2 mSide;

	int mID;
};

//=================================================================================================
// Typedefs
//=================================================================================================

typedef std::list<Agent*> AgentList;

#endif //#ifndef INCLUDED_AGENT_H
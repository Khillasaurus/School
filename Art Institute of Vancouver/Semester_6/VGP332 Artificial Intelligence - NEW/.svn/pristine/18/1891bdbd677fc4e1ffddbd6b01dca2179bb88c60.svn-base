#ifndef INCLUDED_PERCEPTIONMODULE_H
#define INCLUDED_PERCEPTIONMODULE_H

//=================================================================================================
// File:		PerceptionModule.h
// Created:		2012/11/02
// Last Edited:	2012/11/02
// Copyright:	Daniel Schenker
// Description	PerceptionModule.h
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "Agent.h"

// SGE
#include <SGE.h>
using namespace SGE;

//STL
#include <list>

//=================================================================================================
// Enums
//=================================================================================================

namespace PerceptionLevel
{
	enum Type
	{
		Unknown,
		Suspect,
		Confirm
	};
};

//=================================================================================================
// Structs
//=================================================================================================

struct PerceptionData
{
	// Constructors
	PerceptionData()
	: pAgent(NULL)
	, level(PerceptionLevel::Unknown)
	, lastSeenLocation(0.0f, 0.0f)
	, lastHeardLocation(0.0f, 0.0f)
	, lastRecordedTime(FLT_MAX)
	, importance(0.0f)
	{}

	const Agent* pAgent;		//This is too much information? Maybe just store the agent ID
	PerceptionLevel::Type level;
	SVector2 lastSeenLocation;
	SVector2 lastHeardLocation;
	float lastRecordedTime;
	float importance;
};

//=================================================================================================
// Typedefs
//=================================================================================================

typedef std::list<PerceptionData> PerceptionRecords;

//=================================================================================================
// Class Declarations
//=================================================================================================

class PerceptionModule
{
public:
	PerceptionModule(Agent* pOwner);

	void Update(float deltaTime, const AgentList& agents);

	//Accessors
	const PerceptionRecords& GetPerceptionRecords() const;
	float GetViewDistance() const								{ return mViewDistance; }
	float GetViewAngle() const									{ return mViewAngle; }
	float GetHearingRange() const								{ return mHearingRange; }
	float GetMemorySpan() const									{ return mMemorySpan; }

	//Mutators
	void SetViewDistance(float distance)						{ mViewDistance = distance; }
	void SetViewAngle(float angle)								{ mViewAngle = angle; }
	void SetHearingRange(float range)							{ mHearingRange = range; }
	void SetMemorySpan(float span)								{ mMemorySpan = span; }

private:
	//Helper functions
	void AgePerception(float deltaTime);
	void UpdateVision(const AgentList& agents);
	void UpdateHearing();	//TODO
	void UpdateImportance();
	void CalculateImportance(PerceptionData& record);

	//Data
	PerceptionRecords mPerceptionRecords;
	Agent* mpOwner;
	float mViewDistance;
	float mViewAngle;
	float mHearingRange;
	float mMemorySpan;
};

#endif //#ifndef INCLUDED_PERCEPTIONMODULE_H
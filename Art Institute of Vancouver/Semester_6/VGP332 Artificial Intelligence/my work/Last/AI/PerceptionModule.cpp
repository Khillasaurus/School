//=================================================================================================
// File:		PerceptionModule.cpp
// Created:		2012/11/02
// Last Edited:	2012/11/04
// Copyright:	Daniel Schenker
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "PerceptionModule.h"

//STL
#include <algorithm>

//=================================================================================================
// Functors
//=================================================================================================

bool SortImportance(const PerceptionData& a, const PerceptionData& b)
{
	return (a.importance < b.importance);
}

//=================================================================================================
// Class Definitions
//=================================================================================================

PerceptionModule::PerceptionModule(Agent* pOwner)
{
}

void PerceptionModule::Update(float deltaTime, const AgentList& agents)
{
	//Update memory record
	AgePerception(deltaTime);

	//Update hearing perception
	UpdateHearing();

	//Update visual perception
	UpdateVision(agents);

	//Update importance
	UpdateImportance();
}

//Accessors
const PerceptionRecords& PerceptionModule::GetPerceptionRecords() const
{
	return mPerceptionRecords;
}

//Helper functions
void PerceptionModule::AgePerception(float deltaTime)
{
	// Loop through all records
	PerceptionRecords::iterator iter = mPerceptionRecords.begin();
	while(iter != mPerceptionRecords.end())
	{
		// Update recorded time
		PerceptionData& record = (*iter);
		record.lastRecordedTime += deltaTime;
		
		// Check if agent still "remembers' this record
		if(record.lastRecordedTime > mMemorySpan)
		{
			//Remove record
			iter = mPerceptionRecords.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void PerceptionModule::UpdateVision(const AgentList& agents)
{
	const float kViewDistanceSquared = mViewDistance * mViewDistance;
	const float kCosViewAngle = cos(mViewAngle * 0.5f);

	for(AgentList::const_iterator iter = agents.begin();
		iter != agents.end();
		++iter)
	{
		const Agent* pAgent = (*iter);

		// Ignore self
		if(mpOwner == pAgent)
		{
			continue;
		}

		// Check if agent is in range
		const SVector2 kAgentToTarget = pAgent->GetPosition() - mpOwner->GetPosition();
		if(kAgentToTarget.LengthSquared() > kViewDistanceSquared)
		{
			continue;
		}

		// Check if agent is in view cone
		const SVector2 kDirToTarget = Normalize(kAgentToTarget);//This does not check for division by 0, add safeguard later
		if(Dot(kDirToTarget, mpOwner->GetHeading()) < kCosViewAngle)
		{
			continue;
		}

		// Check if we have a record for this agent
		bool hasRecord = false;
		for(PerceptionRecords::iterator recordIter = mPerceptionRecords.begin();
			recordIter != mPerceptionRecords.end();
			++recordIter)
		{
			PerceptionData& record = (*recordIter);
			if(record.pAgent == pAgent)
			{
				record.lastSeenLocation = pAgent->GetPosition();
				record.lastRecordedTime = 0.0f;
				record.level = PerceptionLevel::Confirm;
				hasRecord = true;
				break;
			}
		}

		// Add a new perception record if this agent is new
		if(!hasRecord)
		{
			PerceptionData newRecord;
			newRecord.pAgent = pAgent;
			newRecord.lastSeenLocation = pAgent->GetPosition();
			newRecord.lastRecordedTime = 0.0f;
			newRecord.level = PerceptionLevel::Confirm;
			mPerceptionRecords.push_back(newRecord);
		}
	}
}

void PerceptionModule::UpdateHearing()
{
	// TODO - Requires an event system or stimulus system for tracking things that happen in the game world
}

void PerceptionModule::UpdateImportance()
{
	// Loop through all records
	for(PerceptionRecords::iterator iter = mPerceptionRecords.begin();
		iter != mPerceptionRecords.end();
		++iter)
	{
		PerceptionData& record = (*iter);
		CalculateImportance(record);
	}

	//Sort based on importance
	mPerceptionRecords.sort(SortImportance);
}

void PerceptionModule::CalculateImportance(PerceptionData& record)
{
	float importance = 0.0f;

	// Consider perception level
	if(record.level == PerceptionLevel::Confirm)
	{
		importance += 1000.0f;
	}
	else if(record.level == PerceptionLevel::Suspect)
	{
		importance += 500.0f;
	}

	// Consider distance
	const SVector2 kAgentToTarget = record.lastSeenLocation - mpOwner->GetPosition();
	const float kSeenDistancePercent = 1.0f - Min(kAgentToTarget.Length() / mViewDistance, 1.0f);
	importance += 200.0f * kSeenDistancePercent;

	const SVector2 kAgentToSound = record.lastHeardLocation - mpOwner->GetPosition();
	const float kHeardDistancePercent = 1.0f - Min(kAgentToSound.Length() / mHearingRange, 1.0f);
	importance += 100.0f * kHeardDistancePercent;

	// Consider time
	const float kTimePercent = 1.0f - Min(record.lastRecordedTime / mMemorySpan, 1.0f);
	importance += 50.0f * kTimePercent;

	// Set importance
	record.importance = importance;
}
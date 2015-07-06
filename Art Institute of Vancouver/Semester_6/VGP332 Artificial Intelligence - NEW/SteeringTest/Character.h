#ifndef INCLUDED_CHARACTER_H
#define INCLUDED_CHARACTER_H

//=================================================================================================
// File:		Character.h
// Created:		2012/10/29
// Last Edited:	2012/11/05
// Copyright:	Daniel Schenker
// Description	Character.h
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

// Daniel Schenker
#include <AI.h>

// SGE
#include <SGE.h>
using namespace SGE;

//=================================================================================================
// Class Declarations
//=================================================================================================

class Character : public Agent
{
public:
	Character(int id);
	virtual ~Character();

	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

	void ActivateSeek(bool activate);
	void ActivateArrive(bool activate);
	void ActivateWander(bool activate);

private:
	SGE_Sprite mSprite;

	PerceptionModule* mpPerceptionModule;
	SteeringModule* mpSteeringModule;

	SeekBehavior* mpSeekBehavior;
	ArriveBehavior* mpArriveBehavior;
	WanderBehavior* mpWanderBehavior;
};

#endif //#ifndef INCLUDED_CHARACTER_H
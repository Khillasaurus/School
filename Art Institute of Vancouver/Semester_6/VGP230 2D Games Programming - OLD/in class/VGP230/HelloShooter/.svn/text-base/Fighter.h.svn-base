#ifndef INCLUDED_FIGHTER_H
#define INCLUDED_FIGHTER_H

//=================================================================================================
// Filename:	Fighter.cpp
// Copyright:	Daniel Schenker
// Created:		2012/10/09
// Last Edited:	2012/10/16
// Description:	Fighter header file.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <SGE.h>
using namespace SGE;

//====================================================================================================
// Class Declarations
//====================================================================================================

class Fighter
{
public:
	Fighter();
	~Fighter();

	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

	// Accessors
	const SVector2 & GetPosition() const		{ return mPosition; }
	float GetSpeed() const						{ return mSpeed; }

	// Mutators
	void SetPosition(const SVector2 pos)		{ mPosition = pos; }
	void SetSpeed(float speed)					{ mSpeed = speed; }

private:
	SVector2 mPosition;
	SGE_Sprite mSprite;
	float mSpeed;
};

#endif //#ifndef INCLUDED_FIGHTER_H
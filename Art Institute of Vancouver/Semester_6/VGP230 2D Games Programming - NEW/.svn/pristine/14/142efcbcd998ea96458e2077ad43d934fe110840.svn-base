#ifndef INCLUDED_CHARACTER_H
#define INCLUDED_CHARACTER_H

//=================================================================================================
// Filename:	Character.h
// Copyright:	Daniel Schenker
// Created:		2012/10/30
// Last Edited:	2012/10/31
// Description:	Class for a game character.
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

// SGE
#include <SGE.h>
using namespace SGE;

//Daniel Schenker
#include "Map.h"

//=================================================================================================
// Class Declarations
//=================================================================================================

class Character
{
public:
	//Constructor
	Character();
	//Destructor
	~Character();

	// SGE specific
	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render(const SVector2& offset);

	// Accessors
	float GetMass() const					{ return mMass; }
	const SVector2& GetPosition() const		{ return mPosition; }
	const SVector2& GetVelocity() const		{ return mVelocity; }
	// Mutators
	void SetMass(float mass);
	void SetPosition(const SVector2& pos)	{ mPosition = pos; }
	void SetVelocity(const SVector2& vel)	{ mVelocity = vel; }


private:
	//Graphics
	SGE_Sprite mSprite;

	//Physics
	float mMass;
	SVector2 mPosition;
	SVector2 mVelocity;
};

#endif // #ifndef INCLUDED_CHARACTER_H
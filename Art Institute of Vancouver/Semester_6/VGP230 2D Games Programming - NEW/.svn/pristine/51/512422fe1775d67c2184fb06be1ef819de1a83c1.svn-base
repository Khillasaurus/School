#ifndef INCLUDED_CHARACTER_H
#define INCLUDED_CHARACTER_H

//=================================================================================================
// Filename:	Character.h
// Copyright:	Daniel Schenker
// Created:		2012/10/30
// Last Edited:	2012/10/30
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
	void Update(float deltaTime, const Map& map);
	void Render(const SVector2& offset);

	SRect GetBoundingBox() const;

	// Accessors
	const SVector2& GetPosition() const		{ return mPosition; }
	const SVector2& GetVelocity() const		{ return mVelocity; }
	// Mutators
	void SetPosition(const SVector2& pos)	{ mPosition = pos; }
	void SetVelocity(const SVector2& vel)	{ mVelocity = vel; }


private:
	SGE_Sprite mSprite;

	SVector2 mPosition;
	SVector2 mVelocity;

	bool mJumping;
};

#endif // #ifndef INCLUDED_CHARACTER_H
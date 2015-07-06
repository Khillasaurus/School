#ifndef INCLUDED_BULLET_H
#define INCLUDED_BULLET_H

//=================================================================================================
// Filename:	Bullet.h
// Created by:	Daniel Schenker
// Description:	Class for the bullet projectiles
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

#include <SGE.h>
using namespace SGE;

//=================================================================================================
// Class Declarations
//=================================================================================================

class Bullet
{
public:
	//Constructors
	Bullet();
	//Deconstructor
	~Bullet();

	//SGE Specific
	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

	//General
	void Fire(const SVector2& pos, const SVector2& vel);
	void Kill();

	//Accessors
	const SVector2& GetPosition() const		{ return mPosition; }
	bool IsActive() const					{ return mActive; }
	SCircle GetBoundingCircle() const		{ return SCircle(mPosition, 10.0f); }

	//Mutators
	void SetPosition(const SVector2& pos)	{ mPosition = pos; }

private:
	//Variables
	SGE_Sprite mSprite;
	SVector2 mPosition;
	SVector2 mVelocity;
	bool mActive;
};

#endif //INCLUDED_BULLLET_H
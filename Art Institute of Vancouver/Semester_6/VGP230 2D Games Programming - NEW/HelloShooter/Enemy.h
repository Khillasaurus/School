#ifndef INCLUDED_ENEMY_H
#define INCLUDED_ENEMY_H

//=================================================================================================
// Filename:	Enemy.h
// Copyright:	Daniel Schenker
// Created:		2012/10/16
// Last Edited:	2012/10/16
// Description:	Enemy header file.
//====================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

#include <SGE.h>
using namespace SGE;

//=================================================================================================
// Class Declarations
//=================================================================================================

class Enemy
{
public:
	//Constructors
	Enemy();
	//Deconstructor
	~Enemy();

	//SGE Specific
	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

	//General
	void Spawn(const SVector2& pos);
	void Kill();

	//Accessors
	const SVector2& GetPosition() const		{ return mPosition; }
	bool IsActive() const					{ return mActive; }
	SCircle GetBoundingCircle() const		{ return SCircle(mPosition, 50.0f); }

	//Mutators
	void SetPosition(const SVector2& pos)	{ mPosition = pos; }

private:
	//Variables
	SGE_Sprite mSprite;
	SVector2 mPosition;
	SVector2 mVelocity;
	float mTimer;
	bool mActive;
};

#endif //#ifndef INCLUDED_ENEMY_H
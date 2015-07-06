#ifndef INCLUDED_CHARACTER_H
#define INCLUDED_CHARACTER_H

//====================================================================================================
// Filename:	Character.h
// Created by:	Peter Chan
// Description:	Class for a character.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <SGE.h>
using namespace SGE;

#include "CharacterState.h"
#include "Map.h"

//====================================================================================================
// Enums
//====================================================================================================

enum AnimationState
{
	AS_None = -1,
	AS_Idle,
	AS_Walk,
	AS_Jump,
	AS_Fall,
	AS_Max
};

//====================================================================================================
// Class Declarations
//====================================================================================================

class Character
{
public:
	Character();
	~Character();

	void Load();
	void Unload();
	void Update(float fSeconds, const Map& map);
	void Render(const SVector2& offset);

	void ChangeState(AnimationState as);
	const char* GetCurrentState();

	SRect GetBoundingBox() const;

	// Accessors
	const SVector2& GetPosition() const		{ return mPosition; }
	const SVector2& GetVelocity() const		{ return mVelocity; }
	bool IsFacingLeft() const				{ return mFacingLeft; }

	// Mutators
	void SetPosition(const SVector2& pos)	{ mPosition = pos; }
	void SetVelocity(const SVector2& vel)	{ mVelocity = vel; }
	void SetFacingLeft(bool facingLeft)		{ mFacingLeft = facingLeft; }

private:
	void CheckCollision(float fSeconds, const Map& map);

	CharacterState* mCharacterStates[AS_Max];
	CharacterState* mpCurrentState;

	SVector2 mPosition;
	SVector2 mVelocity;

	bool mFacingLeft;
};

#endif // #ifndef INCLUDED_CHARACTER_H
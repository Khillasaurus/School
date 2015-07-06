#ifndef INCLUDED_CHARACTERSTATE_H
#define INCLUDED_CHARACTERSTATE_H

//====================================================================================================
// Filename:	CharacterState.h
// Created by:	Peter Chan
// Description:	Class for a character state.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <SGE.h>
using namespace SGE;

//====================================================================================================
// Forward Declarations
//====================================================================================================

class Character;

//====================================================================================================
// Class Declarations
//====================================================================================================

class CharacterState
{
public:
	CharacterState(Character* pOwner, const char* name) : mpOwner(pOwner), mName(name) {}
	virtual ~CharacterState() {};

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(float fSeconds) = 0;
	virtual void Render(const SVector2& offset) = 0;

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual SRect GetBoundingBox() const = 0;

	const char* GetName() const	{ return mName; }

protected:
	SGE_Sprite mSprite;

	Character* mpOwner;

	const char* mName;
};

#endif // #ifndef INCLUDED_CHARACTERSTATE_H
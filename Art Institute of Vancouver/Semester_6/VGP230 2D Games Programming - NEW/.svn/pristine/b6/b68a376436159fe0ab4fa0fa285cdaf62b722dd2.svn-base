#ifndef INCLUDED_CHARACTERJUMP_H
#define INCLUDED_CHARACTERJUMP_H

//====================================================================================================
// Filename:	CharacterJump.h
// Created by:	Peter Chan
// Description:	Class for the character jump state.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterState.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class CharacterJump : public CharacterState
{
public:
	CharacterJump(Character* pOwner);
	virtual ~CharacterJump();

	virtual void Load();
	virtual void Unload();
	virtual void Update(float fSeconds);
	virtual void Render(const SVector2& offset);

	virtual void Enter();
	virtual void Exit();

	virtual SRect GetBoundingBox() const;
};

#endif // #ifndef INCLUDED_CHARACTERJUMP_H
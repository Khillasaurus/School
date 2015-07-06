#ifndef INCLUDED_CHARACTERWALK_H
#define INCLUDED_CHARACTERWALK_H

//====================================================================================================
// Filename:	CharacterWalk.h
// Created by:	Peter Chan
// Description:	Class for the character walk state.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterState.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class CharacterWalk : public CharacterState
{
public:
	CharacterWalk(Character* pOwner);
	virtual ~CharacterWalk();

	virtual void Load();
	virtual void Unload();
	virtual void Update(float fSeconds);
	virtual void Render(const SVector2& offset);

	virtual void Enter();
	virtual void Exit();

	virtual SRect GetBoundingBox() const;
};

#endif // #ifndef INCLUDED_CHARACTERWALK_H
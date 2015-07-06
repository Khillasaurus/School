#ifndef INCLUDED_CHARACTERFALL_H
#define INCLUDED_CHARACTERFALL_H

//====================================================================================================
// Filename:	CharacterFall.h
// Created by:	Peter Chan
// Description:	Class for the character fall state.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterState.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class CharacterFall : public CharacterState
{
public:
	CharacterFall(Character* pOwner);
	virtual ~CharacterFall();

	virtual void Load();
	virtual void Unload();
	virtual void Update(float fSeconds);
	virtual void Render(const SVector2& offset);

	virtual void Enter();
	virtual void Exit();

	virtual SRect GetBoundingBox() const;
};

#endif // #ifndef INCLUDED_CHARACTERFALL_H
#ifndef INCLUDED_GAMEPLAY_H
#define INCLUDED_GAMEPLAY_H

//=================================================================================================
// Filename:	Gameplay.h
// Copyright:	Daniel Schenker
// Created:		2012/10/23
// Last Edited:	2012/10/30
// Description:	Gameplay class for game state.
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "BaseState.h"
#include "Character.h"
#include "Map.h"

//=================================================================================================
// Class Declarations
//=================================================================================================

class Gameplay : public BaseState
{
public:
	//Constructor
	Gameplay(GameContext& gc);
	//Destructor
	virtual ~Gameplay();

	// Implements BaseState
	virtual void Load();
	virtual void Unload();
	virtual int Update(float deltaTime);
	virtual void Render();

private:
	Character mCharacter;
	Map mMap;
};

#endif // #ifndef INCLUDED_GAMEPLAY_H
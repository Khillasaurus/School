#ifndef INCLUDED_BASESTATE_H
#define INCLUDED_BASESTATE_H

//=================================================================================================
// Filename:	BaseState.h
// Copyright:	Daniel Schenker
// Created:		2012/10/23
// Last Edited:	2012/10/30
// Description:	Base class for game state.
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

#include "GameContext.h"

//=================================================================================================
// Class Declarations
//=================================================================================================

class BaseState
{
public:
	//Constructor
	BaseState(GameContext& gc);
	//Destructor
	virtual ~BaseState();

	// SGE Specific
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual int Update(float deltaTime) = 0;
	virtual void Render() = 0;

	// Accessors
	int GetScreenWidth() const		{ return kScreenWidth; }
	int GetScreenHeight() const		{ return kScreenHeight; }

protected:
	GameContext& mGameContext;
	// Cache frequently used values
	const int kScreenWidth;
	const int kScreenHeight;
};

#endif //#ifndef INCLUDED_BASESTATE_H
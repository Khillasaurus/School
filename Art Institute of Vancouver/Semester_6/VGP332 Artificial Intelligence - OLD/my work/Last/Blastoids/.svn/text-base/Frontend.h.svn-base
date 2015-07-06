#ifndef INCLUDED_FRONTEND_H
#define INCLUDED_FRONTEND_H

//=================================================================================================
// Filename:	Frontend.h
// Copyright:	Daniel Schenker
// Created:		2012/10/23
// Last Edited:	2012/11/27
// Description:	Frontend class for game state.
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "BaseState.h"
#include "ReturnCodes.h"

// SGE
#include <SGE.h>
using namespace SGE;

//=================================================================================================
// Enumerations
//=================================================================================================

//=================================================================================================
// Class Declarations
//=================================================================================================

class Frontend : public BaseState
{
public:
	//Constructor
	Frontend(GameContext& gc);
	//Destructor
	virtual ~Frontend();

	// Implements BaseState
	virtual void Load();
	virtual void Unload();
	virtual int Update(float deltaTime);
	virtual void Render();

private:
	// General
	SubState::eSubState mSubState;

	// All
	SGE_Cursor mCursor;

	// SubStates
	BaseState* mpMainMenu;
	BaseState* mpStart;
	BaseState* mpNewGame;
	BaseState* mpLoadGame;
	BaseState* mpSettings;
	BaseState* mpGameplay;
	BaseState* mpKeybindings;
	BaseState* mpAudio;
	BaseState* mpVideo;
	BaseState* mpStatistics;
	//BaseState* mpQuit;//Is this neccessary? I think I can just call Unload() and exit the game instead of changing substates.
};

#endif // #ifndef INCLUDED_FRONTEND_H
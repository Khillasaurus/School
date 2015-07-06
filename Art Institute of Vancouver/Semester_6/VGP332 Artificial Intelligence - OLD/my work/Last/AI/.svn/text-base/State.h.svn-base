#ifndef INCLUDED_AI_STATE_H
#define INCLUDED_AI_STATE_H

//=================================================================================================
// File:		State.h
// Created:		2012/11/05
// Last Edited:	2012/11/05
// Created By:	Daniel Schenker
// Description	Templatized class for a FSM state.
//=================================================================================================

//=================================================================================================
// Class Declarations
//=================================================================================================

template <class T>
class State
{
public:
	virtual ~State() {}

	// Called once when the agent enters this state
	virtual void Enter(T* pOwner) = 0;

	// Action to perform during this state
	virtual void Execute(T* pOwner) = 0;

	// Called once when the agent exits this state
	virtual void Exit(T* pOwner) = 0;
};

#endif //#ifndef INCLUDED_AI_STATE_H
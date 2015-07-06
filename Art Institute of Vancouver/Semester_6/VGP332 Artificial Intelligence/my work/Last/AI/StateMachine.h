#ifndef INCLUDED_AI_STATEMACHINE_H
#define INCLUDED_AI_STATEMACHINE_H

//=================================================================================================
// File:		StateMachine.h
// Created By:	Daniel Schenker
// Created:		2012/11/05
// Last Edited:	2012/11/05
// Description	Templatized class for a FSM.
//=================================================================================================

//=================================================================================================
// Includes
//================================================================================================

// Daniel Schenker
#include "State.h"

// STL
#include <vector>

//=================================================================================================
// Class Declarations
//=================================================================================================

template <class T>
class StateMachine
{
public:
	StateMachine(T* pOwner);

	// Function to manage states
	void AddState(State<T>* pState);
	void Purge();

	// Function to update the curent state
	void Update();

	// Function to change state
	void ChangeState(int index);

private:
	T* mpOwner;

	std::vector<State<T>*> mStates;

	int mCurrentState;
};

//=================================================================================================
// Inline Definitions
//=================================================================================================

#include "StateMachine.inl"


#endif //#ifndef INCLUDED_AI_STATEMACHINE_H
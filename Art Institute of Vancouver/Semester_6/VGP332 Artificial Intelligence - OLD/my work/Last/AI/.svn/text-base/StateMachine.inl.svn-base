//=================================================================================================
// File:		StateMachine.inl
// Created By:	Daniel Schenker
// Created:		2012/11/05
// Last Edited:	2012/11/05
//=================================================================================================

//=================================================================================================
// Class Definitions
//=================================================================================================

template <class T>
StateMachine<T>::StateMachine(T* pOwner)
: mpOwner(pOwner)
, mCurrentState(-1)
{
	// Empty
}

//-------------------------------------------------------------------------------------------------

template <class T>
void StateMachine<T>::AddState(State<T>* pState)
{
	mStates.push_back(pState);
}

//-------------------------------------------------------------------------------------------------

template <class T>
void StateMachine<T>::Purge()
{
	const int kNumStates = mStates.size();
	for(int i = 0; i < kNumStates; ++i)
	{
		if(mStates[i] != NULL)
		{
			delete mStates[i];
			mStates[i] = NULL;
		}
	}
	mStates.clear();
}

//-------------------------------------------------------------------------------------------------

template <class T>
void StateMachine<T>::Update()
{
	if(mCurrentState != -1)
	{
		mStates[mCurrentState].Execute(mpOwner);
	}
}

//-------------------------------------------------------------------------------------------------

template <class T>
void StateMachine<T>::ChangeState(int index)
{
	// Exit the current state
	if(mCurrentState != -1)
	{
		mStates[mCurrentState]->Exit(mpOwner);
	}

	// Change state
	mCurrentState = index;

	// Enter the new state
	if(mCurrentState >= 0 && mCurrentState < mStates.size())
	{
		mStates[mCurrentState]->Enter(mpOwner);
	}
}
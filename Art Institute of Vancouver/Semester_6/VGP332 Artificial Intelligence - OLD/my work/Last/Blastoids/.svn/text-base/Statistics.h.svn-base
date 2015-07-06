#ifndef INCLUDED_BLASTOIDS_STATISTICS_H
#define INCLUDED_BLASTOIDS_STATISTICS_H

//=================================================================================================
// Filename:	Statistics.h
// Copyright:	Daniel Schenker
// Created:		2012/11/09
// Last Edited:	2012/11/09
// Description:	Statistics sub-state of the Frontend state.
//				Inherits from BaseState as a sub-state is just a smaller base state with the same
//					properties.
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "BaseState.h"

// SGE
#include <SGE.h>
using namespace SGE;

//=================================================================================================
// Class Declarations
//=================================================================================================

class Statistics : public BaseState
{
public:
	//Constructor
	Statistics(GameContext& gc);
	//Destructor
	virtual ~Statistics();

	// Implements BaseState
	virtual void Load();
	virtual void Unload();
	virtual int Update(float deltaTime);
	virtual void Render();

private:
	//Title
	SGE_Font mTitleFont;
	SVector2 mTitlePos;

	// Buttons
	 // Back
	SGE_Button mBackButton;
	SVector2 mBackButtonPos;
};

#endif // #ifndef INCLUDED_BLASTOIDS_STATISTICS_H
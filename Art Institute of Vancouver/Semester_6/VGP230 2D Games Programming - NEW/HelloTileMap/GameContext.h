#ifndef INCLUDED_GAMECONTEXT_H
#define INCLUDED_GAMECONTEXT_H

//=================================================================================================
// Filename:	GameContext.h
// Copyright:	Daniel Schenker
// Created:		2012/10/30
// Last Edited:	2012/10/30
// Description:	Class for storing gameplay data.
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

// SGE
#include <SGE.h>
using namespace SGE;

//=================================================================================================
// Class Declarations
//=================================================================================================

class GameContext
{
public:
	//Constructors
	GameContext();
	//Destructor
	~GameContext();

	void SaveData(const char* pFileName);
	void LoadData(const char* pFileName);

	//Accessors
	int GetLevel() const			{ return mLevel; }

	//Mutators
	void SetLevel(int level)		{ mLevel = level; }

private:
	int mLevel;
};

#endif //#ifndef INCLUDED_GAMECONTEXT_H
//=================================================================================================
// Filename:	GameContext.cpp
// Copyright:	Daniel Schenker
// Created:		2012/10/30
// Last Edited:	2012/10/30
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

#include "GameContext.h"

//=================================================================================================
// Class Definitions
//=================================================================================================

GameContext::GameContext()
: mLevel(0)
{
	// Empty
}

//-------------------------------------------------------------------------------------------------

GameContext::~GameContext()
{
	// Empty
}

//-------------------------------------------------------------------------------------------------

bool GameContext::SaveData(const char* pFileName)
{
	FILE* pFile = NULL;
	fopen_s(&pFile, pFileName, "w");
	if(pFile != NULL)
	{
		// Write data
		fprintf_s(pFile, "Level: %d\n", mLevel);

		fclose(pFile);
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------

bool GameContext::LoadData(const char* pFileName)
{
	FILE* pFile = NULL;
	fopen_s(&pFile, pFileName, "r");
	if(pFile != NULL)
	{
		// Read data
		fscanf_s(pFile, "%*s %d\n", &mLevel);

		fclose(pFile);
		return true;
	}
	return false;
}
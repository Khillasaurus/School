//=================================================================================================
// Filename:	Map.cpp
// Copyright:	Daniel Schenker
// Created:		2012/10/16
// Last Edited:	2012/10/30
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

#include "Map.h"

//=================================================================================================
// Class Definitions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------------------------------

Map::Map()
: mSprites(NULL)
, mTiles(NULL)
, mColumns(0)
, mRows(0)
, mTileSize(0)
, mSpriteCount(0)
{
	// Empty
}

//-------------------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------------------

Map::~Map()
{
	// Empty
}

//-------------------------------------------------------------------------------------------------

void Map::Load(const char* pLevelFile, const char* pTexturePack)
{
	//Clean up before we start loading anything
	Unload();

	// Load level data
	if(!LoadLevel(pLevelFile))
	{
		Unload();
		return;
	}

	// Load texture pack
	if(!LoadTexturePack(pTexturePack))
	{
		Unload();
		return;
	}
}

//-------------------------------------------------------------------------------------------------

void Map::Unload()
{
	// Release memory
	if(mTiles != NULL)
	{
		delete[] mTiles;
		mTiles = NULL;
	}
	if(mSprites != NULL)
	{
		delete[] mSprites;
		mSprites = NULL;
	}
	// Reset params
	mColumns = 0;
	mRows = 0;
	mTileSize = 0;
	mSpriteCount = 0;
}

//-------------------------------------------------------------------------------------------------

void Map::Render(const SVector2& offset)
{
	for(int y = 0; y < mRows; ++y)
	{
		for(int x = 0; x < mColumns; ++x)
		{
			const int index = x + (y * mColumns);
			const SVector2& pos = mTiles[index].GetPosition();
			const int type = mTiles[index].GetType();
			mSprites[type].SetPosition(pos + offset);
			mSprites[type].Render();
		}
	}
}

//-------------------------------------------------------------------------------------------------

bool Map::LoadLevel(const char* pLevelFile)
{
	FILE* pFile = NULL;
	fopen_s(&pFile, pLevelFile, "r");

	// Read map dimensions
	fscanf_s(pFile, "%*s %d", &mColumns);
	fscanf_s(pFile, "%*s %d", &mRows);
	fscanf_s(pFile, "%*s %d", &mTileSize);

	// Create tile buffer
	mTiles = new Tile[mColumns * mRows];

	// Parse tile data
	fgetc(pFile);
	for(int y = 0; y < mRows; ++y)
	{
		for(int x = 0; x < mColumns; ++x)
		{
			const int index = x + (y * mColumns);
			mTiles[index].SetPosition(SVector2(static_cast<float>(x * mTileSize), static_cast<float>(y * mTileSize)));
			mTiles[index].SetSize(mTileSize);
			mTiles[index].SetType(fgetc(pFile) - '0');
			//mTiles[index].SetWalkable(); TODO
		}
		fgetc(pFile);
	}

	//Close file
	fclose(pFile);
	return true;
}

//-------------------------------------------------------------------------------------------------

bool Map::LoadTexturePack(const char* pTexturePack)
{
	FILE* pFile = NULL;
	fopen_s(&pFile, pTexturePack, "r");

	// Get number of textures
	fscanf_s(pFile, "%*s %d", &mSpriteCount);

	// Create sprite pool
	mSprites = new SGE_Sprite[mSpriteCount];

	// Load textures
	for(int i = 0; i < mSpriteCount; ++i)
	{
		char buffer[128];
		fscanf_s(pFile, "%s", buffer, 128);
		mSprites[i].Load(buffer);
	}

	//Close file
	fclose(pFile);
	return true;
}

//-------------------------------------------------------------------------------------------------
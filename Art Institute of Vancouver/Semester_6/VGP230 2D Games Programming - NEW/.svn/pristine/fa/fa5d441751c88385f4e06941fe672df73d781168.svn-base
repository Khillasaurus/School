#ifndef INCLUDED_MAP_H
#define INCLUDED_MAP_H

//=================================================================================================
// Filename:	Map.h
// Copyright:	Daniel Schenker
// Created:		2012/10/16
// Last Edited:	2012/10/30
// Description:	Class for a tile map.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

// SGE
#include <SGE.h>
using namespace SGE;

// Daniel Schenker
#include "Tile.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class Map
{
public:
	Map();
	~Map();

	// SGE specific
	void Load(const char* pLevelFile, const char* pTexturePack);
	void Unload();
	void Update(float deltaTime);
	void Render(const SVector2& offset);

	// General
	SRect GetBoudingBoxFromSegment(const SLineSegment& line) const;

	// Accessors
	int GetWidth() const						{ return mColumns * mTileSize; };
	int GetHeight()const						{ return mRows * mTileSize; };

private:
	bool LoadLevel(const char* pLevelFile);
	bool LoadTexturePack(const char* pTexturePack);

	SGE_Sprite* mSprites;
	Tile* mTiles;

	int mColumns;
	int mRows;
	int mTileSize;
	int mSpriteCount;
};

#endif //#ifndef INCLUDED_MAP_H
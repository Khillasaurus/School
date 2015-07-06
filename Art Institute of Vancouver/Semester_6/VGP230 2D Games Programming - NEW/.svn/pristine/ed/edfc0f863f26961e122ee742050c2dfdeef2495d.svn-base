#ifndef INCLUDED_MAP_H
#define INCLUDED_MAP_H

//====================================================================================================
// Filename:	Map.h
// Created by:	Peter Chan
// Description:	Class for a tile map.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <SGE.h>
using namespace SGE;

#include "Tile.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class Map
{
public:
	Map();
	~Map();

	void Load(const char* pLevelFile, const char* pTexturePack);
	void Unload();
	void Update(float fSeconds);
	void Render(const SVector2& offset);

	SRect GetBoundingBoxFromSegment(const SLineSegment& line) const;

	int GetWidth() const	{ return mColumns * mTileSize; }
	int GetHeight() const	{ return mRows * mTileSize; }

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

#endif // #ifndef INCLUDED_MAP_H
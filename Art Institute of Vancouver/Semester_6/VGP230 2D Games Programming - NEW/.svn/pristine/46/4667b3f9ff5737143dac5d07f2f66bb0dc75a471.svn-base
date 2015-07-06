#ifndef INCLUDED_MAP_H
#define INCLUDED_MAP_H

#ifndef DSDEBUGMODE
#define DSDEBUGMODE 1
#endif //#ifndef DSDEBUGMODE

//=================================================================================================
// Filename:	Map.h
// Copyright:	Daniel Schenker
// Created:		2012/10/16
// Last Edited:	2012/11/06
// Description:	Class for a tile map.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

// Daniel Schenker
#include "Tile.h"

// SGE
#include <SGE.h>
using namespace SGE;

// Debug
#if DSDEBUGMODE == 1
#include "../SGE/Graphics/CFont.h"
#endif//#if DSDEBUGMODE == 1

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
	bool Update(const SVector2& screenCoordinatesCursorPos, const SVector2& renderOffset, int type);
	void Render(const SVector2& offset);

	// General
	SRect GetBoudingBoxFromSegment(const SLineSegment& line) const;
	bool SaveLevel(const char* pLevelFile);

	// Accessors
	int GetColumns() const							{ return mColumns; }
	int GetHeight() const							{ return mRows * mTileSize; };
	int GetMapOriginWorldCoordinatesX() const;
	int GetMapOriginWorldCoordinatesY() const;
	int GetRows() const								{ return mRows; }
	int GetSelectedNum() const						{ return mSelectedNum; }
	int GetSelectedNumX() const						{ return mSelectedNum % mColumns; }
	int GetSelectedNumY() const						{ return mSelectedNum / mColumns; }
	const Tile* GetTiles() const					{ return mTiles; }
	int GetTileSize() const							{ return mTileSize; };
	int GetWidth() const							{ return mColumns * mTileSize; };

private:
	bool LoadLevel(const char* pLevelFile);
	bool LoadTexturePack(const char* pTexturePack);

	int mColumns;
	int mRows;
	SGE_Sprite mSelectedSprite;
	int mSelectedNum;
	int mSpriteCount;
	SGE_Sprite* mSprites;
	Tile* mTiles;
	int mTileSize;

	///int mStartNum;
	///int mEndNum;
};

#endif //#ifndef INCLUDED_MAP_H
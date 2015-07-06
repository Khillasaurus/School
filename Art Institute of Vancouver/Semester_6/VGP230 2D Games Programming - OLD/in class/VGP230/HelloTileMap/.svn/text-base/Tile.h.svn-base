#ifndef INCLUDED_TILE_H
#define INCLUDED_TILE_H

//=================================================================================================
// Filename:	Tile.h
// Copyright:	Daniel Schenker
// Created:		2012/10/16
// Last Edited:	2012/10/16
// Description:	Tile
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <SGE.h>
using namespace SGE;

//====================================================================================================
// Class Declarations
//====================================================================================================

class Tile
{
public:
	Tile();
	~Tile();

	// Accessors
	const SVector2& GetPosition()				{ return mPosition; }
	int GetSize() const							{ return mSize; }
	int GetType() const							{ return mType; }
	int IsWalkable() const						{ return mWalkable; }

	// Mutators
	void SetPosition(const SVector2& pos)		{ mPosition = pos; }
	void SetSize(int size)						{ mSize = size; }
	void SetType(int type)						{ mType = type; }
	void SetWalkable(bool walkable)				{ mWalkable = walkable; }

private:
	SVector2 mPosition;
	int mSize;
	int mType;
	bool mWalkable;
};

#endif //#ifndef INCLUDED_TILE_H
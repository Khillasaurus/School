#ifndef INCLUDED_TILE_H
#define INCLUDED_TILE_H

//====================================================================================================
// Filename:	Tile.h
// Created by:	Peter Chan
// Description:	Class for a map tile.
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

	SRect GetBoundingBox() const;

	// Accessors
	const SVector2& GetPosition() const		{ return mPosition; }
	int GetSize() const						{ return mSize; }
	int GetType() const						{ return mType; }
	bool IsWalkable() const					{ return mWalkable; }

	// Mutators
	void SetPosition(const SVector2& pos)	{ mPosition = pos; }
	void SetSize(int size)					{ mSize = size; }
	void SetType(int type)					{ mType = type; }
	void SetWalkable(bool walkable)			{ mWalkable = walkable; }

private:
	SVector2 mPosition;
	int mSize;
	int mType;
	bool mWalkable;
};

#endif // #ifndef INCLUDED_TILE_H
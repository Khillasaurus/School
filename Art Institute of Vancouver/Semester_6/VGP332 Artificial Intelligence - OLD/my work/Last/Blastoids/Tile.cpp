//=================================================================================================
// Filename:	Tile.cpp
// Copyright:	Daniel Schenker
// Created:		2012/10/16
// Last Edited:	2012/10/16
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

#include "Tile.h"

//=================================================================================================
// Class Definitions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------------------------------

Tile::Tile()
: mPosition(0.0f, 0.0f)
, mSize(0)
, mType(0)
, mWalkable(true)
{
	// Empty
}

//-------------------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------------------

Tile::~Tile()
{
	// Empty
}

//-------------------------------------------------------------------------------------------------
// General
//-------------------------------------------------------------------------------------------------

SRect Tile::GetBoundingBox() const
{
	return SRect
	(
		mPosition.x,
		mPosition.y,
		mPosition.x + mSize,
		mPosition.y + mSize
	);
}
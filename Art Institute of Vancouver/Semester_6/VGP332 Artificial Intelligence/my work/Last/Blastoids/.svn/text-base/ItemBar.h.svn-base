#ifndef INCLUDED_ITEMBAR_H
#define INCLUDED_ITEMBAR_H

//=================================================================================================
// Filename:	ItemBar.h
// Copyright:	Daniel Schenker
// Created:		2012/11/04
// Last Edited:	2012/11/07
// Description:	Item bar that displays the current tile in use.
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "GameContext.h"

// SGE
#include <SGE.h>
using namespace SGE;

//STL
//#include <vector>

//=================================================================================================
// Class Declarations
//=================================================================================================

class ItemBar
{
public:
	//Constructor
	ItemBar(GameContext& gc);
	//Destructor
	~ItemBar();

	// SGE Specific
	bool Load(const char* pTilesFile);
	void Unload();
	void Update();
	//void Update(int itemInUse);//Maybe instead of passing item in use each time, have a separate Update function that takes no parameters
	void Render();

	//Accessors
	const SVector2& GetOffset() const			{ return mOffset; }
	int GetSelected() const						{ return mSelectedNum; }

	// Mutators
	void SetOffset(const SVector2& offset)		{ mOffset = offset; }
	void SetSelected(unsigned int selected);

private:
	//std::vector<SGE_Sprite> mTileTypes;
	SGE_Sprite* mpTileTypes;
	int mSpriteCount;

	int mLastMouseWheelState;
	SGE_Sprite mSelectedSprite;
	unsigned int mSelectedNum;

	SVector2 mOffset;

};

#endif // #ifndef INCLUDED_ITEMBAR_H